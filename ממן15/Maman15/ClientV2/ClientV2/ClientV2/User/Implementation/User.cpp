#include <iostream>
#include <iomanip>
#include <cstdio>
#include <filesystem>
#include <vector>

#include <boost/io/ios_state.hpp>

#include "../../Utils/Headers/Serialize.h"
#include "../../Utils/Headers/Checksum.h"

#include "../../Encryption/Headers/AESWrapper.h"

#include "../../Request/Headers/Request/Request.h"
#include "../../Request/Headers/UserRegisteration/UserRegisterationRequest.h"
#include "../../Request/Headers/PublicKeyExchange/PublicKeyExchangeRequest.h"
#include "../../Request/Headers/FileUpload/FileUploadRequest.h"
#include "../../Request/Headers/CRC/CRCRequest.h"

#include "../../Response/Headers/ResponseHeader.h"
#include "../../Response/Headers/FileUploadSuccess.h"
#include "../../Response/Headers/RegisterResponse.h"
#include "../../Response/Headers/AESKeyExchange.h"

#include "./../Header/User.h"

#include <boost/asio/ip/tcp.hpp>
#include <boost/filesystem.hpp>

void User::sign_up(tcp::iostream& tcp_stream) const
{
    if (this->client_config_.is_full()) {
        return;
    }

    const UserRegistrationRequest request(this->client_config_.get_username());
    tcp_stream <<= request.getHeader();
    tcp_stream <<= request.getPayload();

    ResponseHeader response_header;
    tcp_stream >>= response_header;

    if (ResponseCode::register_success != response_header.get_code()) {
        std::cerr << "Error! Got response code " << static_cast<uint16_t>(response_header.get_code()) << std::endl;
        return;
    }

    RegisterSuccessPayload response_payload;
    tcp_stream >>= response_payload;

    this->client_config_.set_client_id(response_payload.client_id);
}

void User::do_key_exchange(tcp::iostream& tcpStream) {
	const PublicKeyExchangeRequest request(this->client_config_.get_client_id(), this->client_config_.get_username(),
	                                       this->client_config_.get_public_key());
    tcpStream <<= request.getHeader();
    tcpStream <<= request.getPayload();

    ResponseHeader response_header;
    tcpStream >>= response_header;

    if (ResponseCode::aes_key_exchange != response_header.get_code()) {
        std::cerr << "Error! Got response code " << static_cast<uint16_t>(response_header.get_code()) << std::endl;
        return;
    }

    AESKeyExchangePayload response_payload;
    tcpStream >>= response_payload;

	const std::string aes_key = this->rsa_.decrypt(response_payload.encrypted_aes_key.data(), RSAPrivateWrapper::BLOCKSIZE);
    this->aes_.setKey(aes_key);
}

void User::upload_file(tcp::iostream& tcp_stream, const std::string& file_name) {
    ResponseHeader response_header;
    bool is_correct_crc = false;


    const uintmax_t file_size = filesystem::file_size(file_name);
    FILE* file = std::fopen(file_name.c_str(), "rb");
    std::vector<uint8_t> file_contents(file_size);
    std::fread(file_contents.data(), sizeof(uint8_t), file_size, file);
    std::fclose(file);

    const uint32_t own_checksum = crc32_buf(file_contents.data(), file_size);

    for (size_t retries = crc_retry_count; !is_correct_crc && retries > 0; retries--) {
	    const uint32_t server_checksum = this->send_file(tcp_stream, file_name, file_contents, file_size);

        is_correct_crc = own_checksum == server_checksum;
        if (is_correct_crc) {
            break;
        }

        incorrect_crc_retry_request request(this->client_config_.get_client_id(), file_name);
        tcp_stream <<= request.getHeader();
        tcp_stream <<= request.getPayload();
        tcp_stream >>= response_header;

        std::cerr << "Got response code " << static_cast<uint16_t>(response_header.get_code()) << std::endl;
    }

    if (is_correct_crc) {
        std::cout << "Got correct CRC for " << file_name << std::endl;
        const correct_crc_request request(this->client_config_.get_client_id(), file_name);
        tcp_stream <<= request.getHeader();
        tcp_stream <<= request.getPayload();
    }
    else {
        std::cout << "CRC retries exhausted, failed to upload " << file_name << std::endl;
        const incorrect_crc_final_request request(this->client_config_.get_client_id(), file_name);
        tcp_stream <<= request.getHeader();
        tcp_stream <<= request.getPayload();
    }

    tcp_stream >>= response_header;
}

uint32_t User::send_file(boost::asio::ip::tcp::iostream& tcp_stream, const std::string& file_name, const std::vector<uint8_t>& file_contents, uint32_t file_size) {
    boost::io::ios_all_saver guard(std::cout);
    const std::string encrypted = this->aes_.encrypt(file_contents.data(), file_size);

    const FileUploadRequest request(this->client_config_.get_client_id(), file_name, encrypted.size());
    tcp_stream <<= request.getHeader();
    tcp_stream <<= request.getPayload();
    tcp_stream <<= encrypted;

    ResponseHeader response_header;
    tcp_stream >>= response_header;

    if (ResponseCode::file_upload_success != response_header.get_code()) {
        std::cerr << "Error! Got response code " << static_cast<uint16_t>(response_header.get_code()) << std::endl;
        return -1;
    }

    FileUploadSuccessPayload response_payload;
    tcp_stream >>= response_payload;

    return response_payload.checksum;
}
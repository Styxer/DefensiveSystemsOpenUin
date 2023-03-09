#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <boost/asio.hpp>

#include "../../Config/Headers/ClientConfig.h"

#include "../../Encryption/Headers/RSAWrapper.h"
#include "../../Encryption/Headers/AESWrapper.h"

#pragma once

using boost::asio::ip::tcp;

class User {
public:
	User(ClientConfig& client_config) : client_config_(client_config), rsa_(client_config.get_private_key()), aes_() {}

	void sign_up(tcp::iostream& tcp_stream) const;

	void do_key_exchange(tcp::iostream& tcp_stream);

	void upload_file(tcp::iostream& tcp_stream, const std::string& file_name);

private:
	ClientConfig& client_config_;
	RSAPrivateWrapper rsa_;
	AESWrapper aes_;

	uint32_t send_file(tcp::iostream& tcp_stream, const std::string& file_name, const std::vector<uint8_t>& file_contents, uint32_t file_size);
};

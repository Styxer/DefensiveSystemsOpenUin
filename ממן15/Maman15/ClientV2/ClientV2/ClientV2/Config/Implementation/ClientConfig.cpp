#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>

#include <boost/algorithm/hex.hpp>

#include "../../Utils/Headers/Serialize.h"
#include "../../Utils/Headers/Constants.h"

#include "../../Encryption/Headers/Base64Wrapper.h"
#include "../../Encryption/Headers/RSAWrapper.h"

#include "../Headers/ClientConfig.h"

ClientConfig::ClientConfig(const std::string& filename) : file_(filename), username_(), client_id_({ 0 }), private_key_(), public_key_(), is_full_(false) {
    if (!this->file_.is_open()) {
        this->file_.clear();
        this->file_.open(filename, std::ios::out);
        this->file_.close();
        this->file_.open(filename);
        return;
    }

    std::getline(this->file_, this->username_);

    std::string client_id_hex;
    this->file_ >> client_id_hex;
    boost::algorithm::unhex(client_id_hex.begin(), client_id_hex.end(), this->client_id_.begin());

    std::string private_key_base64;
    for (std::string line; std::getline(this->file_, line); ) {
        private_key_base64 += line;
    }
    this->private_key_ = Base64Wrapper::decode(private_key_base64);

    this->is_full_ = true;
}

bool ClientConfig::is_full() const noexcept {
    return this->is_full_;
}

const std::string& ClientConfig::get_username() const noexcept {
    return this->username_;
}

void ClientConfig::set_username(const std::string& username) {
    if (username.size() > max_username_length) {
        throw std::runtime_error::runtime_error("Username too long!");
    }

    if (!this->username_.empty()) {
        return;
    }

    this->username_ = username;
    this->file_ << username << std::endl;
}

const client_id& ClientConfig::get_client_id() const noexcept {
    return this->client_id_;
}

void ClientConfig::set_client_id(const client_id& clientID) {
    std::string clientIDHex(2 * clientID.size(), '\0');
    std::copy(clientID.begin(), clientID.end(), this->client_id_.begin());
    boost::algorithm::hex(this->client_id_.begin(), this->client_id_.end(), clientIDHex.begin());
    this->file_ << clientIDHex << std::endl;
    this->file_ << Base64Wrapper::encode(this->private_key_) << std::endl;
}

const std::string& ClientConfig::get_public_key() noexcept {
    if (this->public_key_.empty()) {
	    const RSAPrivateWrapper wrapper(this->public_key_);
        this->public_key_ = wrapper.getPublicKey();
    }

    return this->public_key_;
}

const std::string& ClientConfig::get_private_key() noexcept {
    if (this->private_key_.empty()) {
	    const RSAPrivateWrapper wrapper;
        this->private_key_ = wrapper.getPrivateKey();
        this->private_key_ = wrapper.getPublicKey();
    }

    return this->private_key_;
}
#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <boost/asio.hpp>

#include "../../Utils/Headers/Constants.h"

#include "../../Config/ClientConfig.h"

#include "../encryption/RSAWrapper.h"
#include "../encryption/AESWrapper.h"

#pragma once

using boost::asio::ip::tcp;

class User {
public:
	User(ClientConfig& clientConfig) : _clientConfig(clientConfig), _rsa(clientConfig.getPrivateKey()), _aes() {};

	void signUp(tcp::iostream& tcpStream);

	void doKeyExchange(tcp::iostream& tcpStream);

	void uploadFile(tcp::iostream& tcpStream, const std::string& filename);

private:
	ClientConfig& _clientConfig;
	RSAPrivateWrapper _rsa;
	AESWrapper _aes;

	uint32_t _sendFile(tcp::iostream& tcpStream, const std::string& filename, const std::vector<uint8_t>& fileContents, uint32_t fileSize);
};

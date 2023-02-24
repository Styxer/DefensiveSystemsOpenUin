#pragma once

#include "RSAHandler.h"

class rsa_private_handler
{
private:
#pragma region Variables
	RSA::PrivateKey private_key_;
#pragma endregion
	/*rsa_private_handler(const rsa_private_handler& rsa_private);
	rsa_private_handler& operator=(const rsa_private_handler& rsa_private);*/
protected:

public:
#pragma region Ctors
	rsa_private_handler();
	rsa_private_handler(const uint8_t* key, unsigned int length);
	rsa_private_handler(const std::string& key);
#pragma endregion


#pragma region Key Related Functions
	std::string get_private_key() const;
	uint8_t* get_private_key(uint8_t* key_out, unsigned int len) const;

	std::string get_public_key() const;
	uint8_t* get_public_key(uint8_t* key_out, unsigned int len) const;

	static constexpr unsigned int block_size = 128;
#pragma endregion

#pragma region Decrypt
	std::string decrypt(const std::string& cipher) const;
	std::string decrypt(const uint8_t* cipher, unsigned int len) const;
#pragma endregion


};

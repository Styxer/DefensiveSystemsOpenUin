#pragma once

#include "RSAHandler.h"

class rsa_private_wrapper
{
private:
	rsa_private_wrapper(const rsa_private_wrapper& rsa_private);
	rsa_private_wrapper& operator=(const rsa_private_wrapper& rsa_private);
protected:

public:
#pragma region Ctors
	rsa_private_wrapper();
	rsa_private_wrapper(const uint8_t* key, unsigned int length);
	rsa_private_wrapper(const std::string& key);
#pragma endregion

#pragma region Dtor
	~rsa_private_wrapper();
#pragma endregion

#pragma region Key Related Functions
	std::string get_private_key() const;
	uint8_t* get_private_key(uint8_t* key_out, unsigned int length) const;

	std::string get_public_key() const;
	uint8_t* get_public_key(uint8_t* key_out, unsigned int length) const;
#pragma endregion

#pragma region Decrypt
	std::string decrypt(const std::string& cipher);
	std::string decrypt(const uint8_t* cipher, unsigned int length);
#pragma endregion


};

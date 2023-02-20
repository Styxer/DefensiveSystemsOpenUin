#pragma once

#include "RSAHandler.h"

class public_rsa_handler
{
public:
#pragma region Variables
	/*static constexpr unsigned int key_size = 160;
	static constexpr unsigned int bits = 1024;*/
#pragma endregion

#pragma region Ctors
	public_rsa_handler(const std::string& key)					 = delete;
	public_rsa_handler(const uint8_t* key, unsigned int length)  = delete;
#pragma endregion

#pragma region Dtors
	~public_rsa_handler()										 = delete;
#pragma endregion

#pragma region Functions

#pragma region key related functions
	std::string get_public_key() const;
	uint8_t* get_public_key(uint8_t* key_out, unsigned int len) const;
#pragma endregion


#pragma region Encrypt
	std::string encrypt(const std::string& plain);
	std::string encrypt(const uint8_t* plain, unsigned int len);
#pragma endregion

#pragma endregion

protected:

private:
#pragma region Variables
	/*CryptoPP::AutoSeededRandomPool rng_pool_;
	CryptoPP::RSA::PublicKey public_key_;	*/
#pragma endregion

#pragma region Copy Ctor
	public_rsa_handler(const public_rsa_handler& rsa);
#pragma endregion

#pragma region Opreator overrides
	public_rsa_handler& operator=(const public_rsa_handler& rsa);
#pragma endregion

};

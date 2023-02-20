#pragma once
#include <string>
#include <cstddef>
#include <aes.h>
#include <osrng.h>



class aes_handler
{
public:
#pragma region Variables
	static constexpr unsigned int default_key_length = 16;
	static constexpr size_t block_size = CryptoPP::AES::BLOCKSIZE;
#pragma endregion

#pragma region Function

#pragma region key related functions
	static uint8_t* generate_key(uint8_t* buffer, unsigned int len);
	void set_key(const std::string& new_key);
	const uint8_t* get_key() const;
#pragma endregion


#pragma region Encrypt and Decrypt
	std::string encrypt(const uint8_t* plain_data, unsigned int len);
	std::string decrypt(const uint8_t* encrypted_data, unsigned int len);
#pragma endregion

#pragma endregion

#pragma region Ctor
	aes_handler();
	aes_handler(uint8_t* key, unsigned int len);
#pragma endregion



protected:
	
private:
	uint8_t key_[default_key_length];
	aes_handler(const aes_handler& aes);

	CryptoPP::AutoSeededRandomPool rng_;
	CryptoPP::SecByteBlock generate_block();
};

#pragma once
#pragma once

#include <string>
#include <cstddef>

#include <aes.h>


class AESWrapper
{
public:
	static constexpr unsigned int DEFAULT_KEYLENGTH = 16;
	static constexpr size_t BLOCKSIZE = CryptoPP::AES::BLOCKSIZE;
private:
	uint8_t _key[DEFAULT_KEYLENGTH];
	AESWrapper(const AESWrapper& aes);
public:
	static uint8_t* GenerateKey(uint8_t* buffer, unsigned int length);

	AESWrapper();
	AESWrapper(const uint8_t* key, unsigned int size);
	~AESWrapper();

	void setKey(const std::string& newKey);

	const uint8_t* getKey() const;

	std::string encrypt(const uint8_t* plain, unsigned int length);
	std::string decrypt(const uint8_t* cipher, unsigned int length);
};

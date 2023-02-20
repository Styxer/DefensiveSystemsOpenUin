#include "AESHandler.h"

#include <modes.h>
#include <aes.h>
#include <filters.h>
#include <stdexcept>
#include <immintrin.h>

using namespace CryptoPP;


#pragma region Ctors
aes_handler::aes_handler()
{
	generate_key(key_, default_key_length);
}

aes_handler::aes_handler(uint8_t* key, unsigned len)
{
	if (len != default_key_length)
		throw std::length_error("key length must exactly be 16 bytes");
	memcpy_s(key_, default_key_length, key, len);
}

#pragma endregion


#pragma region Key Related Fucntions
uint8_t* aes_handler::generate_key(uint8_t* buffer, unsigned len)
{
	for (size_t i = 0; i < len; i += sizeof(unsigned int))
		_rdrand32_step(reinterpret_cast<unsigned int*>(&buffer[i]));
	return buffer;
}

void aes_handler::set_key(const std::string& new_key)
{
	std::copy(new_key.begin(), new_key.end(), this->key_);
}

const uint8_t* aes_handler::get_key() const
{
	return key_;
}
#pragma endregion


#pragma region Encrypt
std::string aes_handler::encrypt(const uint8_t* plain_data, unsigned int len)
{
	//CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE] = { 0 };
	SecByteBlock iv = generate_block();

	AES::Encryption aes_encryption(key_, default_key_length);
	CBC_Mode_ExternalCipher::Encryption cbc_encryption(aes_encryption, iv);

	std::string cipher;
	StreamTransformationFilter stf_encryption(cbc_encryption, new CryptoPP::StringSink(cipher));
	stf_encryption.Put(plain_data, len);
	stf_encryption.MessageEnd();

	return cipher;
}
#pragma endregion

std::string aes_handler::decrypt(const uint8_t* encrypted_data, unsigned int len)
{
	//CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE] = { 0 };	
	SecByteBlock iv = generate_block();

	AES::Decryption aes_decryption(key_, default_key_length);
	CBC_Mode_ExternalCipher::Decryption cbc_decryption(aes_decryption, iv);

	std::string decrypted;
	StreamTransformationFilter stf_decryption(cbc_decryption, new CryptoPP::StringSink(decrypted));
	stf_decryption.Put(encrypted_data, len);
	stf_decryption.MessageEnd();

	return decrypted;
}

SecByteBlock aes_handler::generate_block()
{
	SecByteBlock block(CryptoPP::AES::BLOCKSIZE);
	prng.GenerateBlock(block, block.size());
	return  block;
}




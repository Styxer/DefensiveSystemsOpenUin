#include "PrivateRSAHandler.h"


rsa_private_handler::rsa_private_handler()
{
	private_key_.Initialize(rng_, bits);
}

rsa_private_handler::rsa_private_handler(const uint8_t* key, const unsigned int len)
{
	StringSource string_source((key), len, true);
	private_key_.Load(string_source);
}

rsa_private_handler::rsa_private_handler(const std::string& key)
{
	StringSource string_source(key, true);
	private_key_.Load(string_source);
}

#pragma region Key Related Functions

#pragma region Private key functions
std::string rsa_private_handler::get_private_key() const
{
	std::string key;
	StringSink string_sink(key);
	private_key_.Save(string_sink);
	return key;
}

uint8_t* rsa_private_handler::get_private_key(uint8_t* key_out, const unsigned int len) const
{
	ArraySink array_sink((key_out), len);
	private_key_.Save(array_sink);
	return key_out;
}
#pragma endregion

#pragma region Public Key Functions
std::string rsa_private_handler::get_public_key() const
{
	const RSAFunction public_key(private_key_);
	std::string key;
	StringSink string_sink(key);
	public_key.Save(string_sink);
	return key;
}

uint8_t* rsa_private_handler::get_public_key(uint8_t* key_out, const unsigned int len) const
{
	const RSAFunction public_key(private_key_);
	ArraySink array_sink((key_out), len);
	public_key.Save(array_sink);
	return key_out;
}
#pragma endregion

#pragma endregion

#pragma region Decrypt Functions

std::string rsa_private_handler::decrypt(const std::string& cipher) const
{
	std::string decrypted;
	const RSAES_OAEP_SHA_Decryptor decryption(private_key_);
	StringSource string_source(cipher, true
		, new PK_DecryptorFilter(rng_, decryption, new StringSink(decrypted)));
	return decrypted;
}

std::string rsa_private_handler::decrypt(const uint8_t* cipher, const unsigned int len) const
{
	std::string decrypted;
	const RSAES_OAEP_SHA_Decryptor decryption(private_key_);
	StringSource ss_cipher((cipher), len, true
		, new PK_DecryptorFilter(rng_, decryption, new StringSink(decrypted)));
	return decrypted;
}
#pragma endregion


#include "PublicRSAHandler.h"

#pragma region Ctor
public_rsa_handler::public_rsa_handler(const std::string& key)
{
	StringSource string_source(key, true);
	public_key_.Load(string_source);	
}

public_rsa_handler::public_rsa_handler(const uint8_t* key, const unsigned int len)
{
	StringSource string_source((key), len, true);
	public_key_.Load(string_source);
}
#pragma endregion

#pragma region Key Related Functions
std::string public_rsa_handler::get_public_key() const
{
	std::string key;
	StringSink string_sink(key);
	public_key_.Save(string_sink);
	return key;
}

uint8_t* public_rsa_handler::get_public_key(uint8_t* key_out, const unsigned int len) const
{
	ArraySink array_sink((key_out), len);
	public_key_.Save(array_sink);
	return key_out;
}
#pragma endregion

#pragma region Encrpy Functions
std::string public_rsa_handler::encrypt(const std::string& plain) const
{
	std::string cipher;
	const RSAES_OAEP_SHA_Encryptor encryption(public_key_);
	StringSource string_source(plain, true
		, new PK_EncryptorFilter(rng_, encryption, new StringSink(cipher)));
	return cipher;
}

std::string public_rsa_handler::encrypt(const uint8_t* plain, const unsigned int len) const
{
	std::string cipher;
	const RSAES_OAEP_SHA_Encryptor encryption(public_key_);
	StringSource string_source((plain), len, true
		, new PK_EncryptorFilter(rng_, encryption, new CryptoPP::StringSink(cipher)));
	return cipher;
}
#pragma endregion



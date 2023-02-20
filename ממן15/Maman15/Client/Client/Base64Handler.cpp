#include "Base64Handler.h"

std::string base64_handler::decode(const std::string& str)
{
	std::string encoded;
	CryptoPP::StringSource string_source(str, true,
		new CryptoPP::Base64Encoder(
			new CryptoPP::StringSink(encoded)
		) 
	); 
	return  encoded;
}

std::string base64_handler::encode(const std::string& str)
{
	std::string decoded;
	CryptoPP::StringSource string_source(str, true,
		new CryptoPP::Base64Decoder(
			new CryptoPP::StringSink(decoded)
		) 
	); 

	return decoded;
}

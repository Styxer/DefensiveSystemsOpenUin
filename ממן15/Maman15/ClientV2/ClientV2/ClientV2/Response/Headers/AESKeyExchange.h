#pragma once

#include <array>

#include "../../Encryption/Headers/RSAWrapper.h"
#include "../../Utils/Headers/Constants.h"
#include "../../Utils/Headers/Serialize.h"


#include "../../Response/Headers/ResponseHeader.h"


struct AESKeyExchangePayload {
	client_id client_id;
	std::array<uint8_t, RSAPrivateWrapper::BLOCKSIZE> encrypted_aes_key;
};

inline std::istream& operator >>=(std::istream& in, AESKeyExchangePayload& payload) {
	in >>= payload.client_id;
	in >>= payload.encrypted_aes_key;
	return in;
}
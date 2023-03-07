#pragma once
#include <array>
#include <cstdint>
#include "../../../Utils/Headers/Constants.h"
#include "../../../Encryption/Headers/RSAWrapper.h"

struct PublicKeyExchangePayload {
	user_name user_name;
	std::array<uint8_t, RSAPublicWrapper::KEYSIZE> public_key;
};

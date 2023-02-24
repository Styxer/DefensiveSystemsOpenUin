#pragma once
#include <array>
#include <cstdint>

#include "Constants.h"
#include "PublicRSAHandler.h"

struct PublicKeyExchangePayload {
	username user_name;
	std::array<uint8_t, public_rsa_handler::key_size> public_key;
};

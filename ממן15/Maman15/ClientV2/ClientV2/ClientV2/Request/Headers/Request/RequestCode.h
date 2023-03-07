#pragma once
#include <cstdint>

enum class RequestCode : uint16_t {
	user_registration = 1100,
	public_key_exchange = 1101,
	file_upload = 1103,
	correct_crc = 1104,
	incorrect_crc_retry = 1105,
	incorrect_crc_final = 1106
};

#pragma once
#include <cstdint>

enum class ResponseCode : uint16_t {
	register_success = 2100,
	register_failure = 2101,
	aes_key_exchange = 2102,
	file_upload_success = 2103,
	ack = 2104,
	server_error = 2105
};

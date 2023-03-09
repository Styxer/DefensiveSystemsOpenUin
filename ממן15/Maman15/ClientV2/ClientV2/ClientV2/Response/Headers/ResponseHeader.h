#pragma once
#include <cstdint>
#include <istream>

#include "ResponseCode.h"


class ResponseHeader {
public:
	ResponseHeader(const uint8_t server_version, const ResponseCode code, const uint32_t payload_size) : server_version_(server_version), code_(code), payload_size_(payload_size) {}
	ResponseHeader() : ResponseHeader(0, ResponseCode::server_error, 0) {}

	friend std::istream& operator >>=(std::istream& in, ResponseHeader& response_header);

	uint8_t get_server_version() const noexcept;

	ResponseCode get_code() const noexcept;

	uint32_t get_payload_size() const noexcept;

private:
	uint8_t server_version_;
	ResponseCode code_;
	uint32_t payload_size_;
};

std::istream& operator >>=(std::istream& in, ResponseHeader& response_header);



#include "../../Utils/Headers/Serialize.h"
#include "./../Headers/ResponseHeader.h"
#include "./../Headers/ResponseCode.h"

class ResponseHeader;

std::istream& operator >>=(std::istream& in, ResponseHeader& response_header) {
	in >>= response_header.server_version_;
	in >>= response_header.code_;
	in >>= response_header.payload_size_;
	return in;
}

uint8_t ResponseHeader::get_server_version() const noexcept {
	return this->server_version_;
}

ResponseCode ResponseHeader::get_code() const noexcept {
	return this->code_;
}

uint32_t ResponseHeader::get_payload_size() const noexcept {
	return this->payload_size_;
}
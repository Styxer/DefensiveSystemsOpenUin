#pragma once

#include <ostream>

#include "RequestCode.h"
#include "../../../Utils/Headers/Constants.h"

class RequestHeader {
public:
	RequestHeader(const client_id& client_id, RequestCode code, uint32_t payload_size);

	RequestHeader(const RequestCode code, const uint32_t payload_size) : RequestHeader({ 0 }, code, payload_size) {}

	const client_id& get_client_id();

	void set_client_id(const client_id& client_id) noexcept;

	friend std::ostream& operator <<=(std::ostream& out, RequestHeader const& request_header);

private:
	client_id client_id_;
	uint8_t client_version_;
	RequestCode code_;
	uint32_t payload_size_;
};

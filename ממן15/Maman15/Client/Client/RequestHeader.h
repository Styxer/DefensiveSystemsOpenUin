#pragma once
#include <cstdint>
#include <ostream>

#include "RequestCode.h"
#include "Constants.h"

class  RequestHeader
{
public:
#pragma region Ctors
	RequestHeader(const client_id& client_id, RequestCode code, uint32_t payload_size);
	RequestHeader(const RequestCode code, const uint32_t payload_size) : RequestHeader({ 0 }, code, payload_size) {}
#pragma endregion

#pragma region Get And Set Client ID
	const client_id& get_client_id();
	void set_client_id(const client_id& client_id) noexcept;
#pragma endregion

	friend std::ostream& operator <<=(std::ostream& out, RequestHeader const& request_header);

protected:

private:
	client_id client_id_;
	uint8_t client_version_;
	RequestCode code_;
	uint32_t payload_size_;

};





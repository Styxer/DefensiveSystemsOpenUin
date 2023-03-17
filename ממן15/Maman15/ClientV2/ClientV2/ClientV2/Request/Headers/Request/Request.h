#pragma once
#include "RequestCode.h"

#include "../../../Utils/Headers/Constants.h"

#include "RequestHeader.h"

template <RequestCode C, class T>
class Request {
public:
    Request(const client_id& client_id, const T& payload, const uint32_t payload_size = sizeof(T)) : header_(client_id, C, payload_size), payload_(payload) {}
    explicit Request(const client_id& client_id, const uint32_t payload_size = sizeof(T)) : header_(client_id, C, payload_size), payload_() {}
    Request() : Request({ 0 }) {}

    [[nodiscard]] const RequestHeader& get_header() const noexcept {
        return this->header_;
    }

    const T& get_payload() const noexcept {
        return this->payload_;
    }

protected:
    RequestHeader header_;
    T payload_;
};

std::ostream& operator<<=(std::ostream& out, RequestHeader const& request_header);

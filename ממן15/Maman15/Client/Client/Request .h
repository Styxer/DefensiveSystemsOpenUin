#pragma once
#include "RequestCode.h"
#include "RequestHeader.h"
#include "Constants.h"

template <RequestCode C, class T>
class Request {
public:
#pragma region Ctors
    Request(const client_id& client_id, const T& payload, const uint32_t payload_size = sizeof(T)) : header_(client_id, C, payload_size), payload_(payload) {}
    explicit Request(const client_id& client_id, const uint32_t payload_size = sizeof(T)) : header_(client_id, C, payload_size), payload_() {}
    Request() : Request({ 0 }) {}
#pragma endregion


    const RequestHeader& Request<C, T>::getHeader() const noexcept {
        return this->header_;
    }

    const T& Request<C, T>::getPayload() const noexcept {
        return this->payload_;
    }

protected:
    RequestHeader header_;
    T payload_;

private:
};

std::ostream& operator<<=(std::ostream& out, RequestHeader const& request_header);

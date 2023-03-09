#include "../../Utils/Headers/Constants.h"
#include "../../Utils/Headers/Serialize.h"

#include "./../Headers/Request/Request.h"

std::ostream& operator <<=(std::ostream& out, RequestHeader const& request_header) {
    out <<= request_header.client_id_;
    out <<= request_header.client_version_;
    out <<= request_header.code_;
    out <<= request_header.payload_size_;
    return out;
}

RequestHeader::RequestHeader(const client_id& client_id, const RequestCode code, const uint32_t payload_size) : client_id_({ 0 }),
                                                                                                                client_version_(client_version),
                                                                                                                code_(code),
                                                                                                                payload_size_(payload_size) {
    this->set_client_id(client_id);
}

const client_id& RequestHeader::get_client_id() const
{
    return this->client_id_;
}

void RequestHeader::set_client_id(const client_id& client_id) noexcept {
    std::copy(client_id.begin(), client_id.end(), this->client_id_.begin());
}

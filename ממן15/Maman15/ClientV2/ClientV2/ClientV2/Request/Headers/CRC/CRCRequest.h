#pragma once
#include <array>
#include <string>

#include "CRCRequestPayload.h"
#include "../../../Utils/Headers/Constants.h"
#include "../../../Utils/Headers/Serialize.h"

#include "./../Request/Request.h"

template<RequestCode  C>
class CRCRequest : public Request<C, CRCRequestPayload> {
public:
    CRCRequest(const client_id& client_id, const std::string& filename) : Request(client_id) {
        std::copy(client_id.begin(), client_id.end(), this->_payload.clientID.begin());
        std::copy(filename.begin(), filename.end(), this->_payload.filename.begin());
    }
};

using correct_crc_request = CRCRequest<RequestCode::correct_crc>;
using incorrect_crc_retry_request = CRCRequest<RequestCode::incorrect_crc_retry>;
using incorrect_crc_final_request = CRCRequest<RequestCode::incorrect_crc_final>;

inline std::ostream& operator <<=(std::ostream& out, CRCRequestPayload const& payload) {
    out <<= payload.client_id;
    out <<= payload.file_name;
    return out;
}

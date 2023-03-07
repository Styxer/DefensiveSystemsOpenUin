#pragma once
#include <algorithm>
#include <string>

#include "../../../Utils/Headers/Constants.h"
#include "../../../Utils/Headers/Serialize.h"
#include "PublicKeyExchangePayload.h"

class PublicKeyExchangeRequest : public Request<RequestCode::PUBLIC_KEY_EXCHANGE, PublicKeyExchangePayload> {
public:
    PublicKeyExchangeRequest(const client_id& client_id, const std::string& user_name, const std::string& public_key) : Request(client_id) {
        std::copy(user_name.begin(), user_name.end(), this->payload_.userName.begin());
        std::copy(public_key.begin(), public_key.end(), this->payload_.publicKey.begin());
    }
};

inline std::ostream& operator <<=(std::ostream& out, PublicKeyExchangePayload const& payload) {
    out <<= payload.user_name;
    out <<= payload.public_key;
    return out;
}

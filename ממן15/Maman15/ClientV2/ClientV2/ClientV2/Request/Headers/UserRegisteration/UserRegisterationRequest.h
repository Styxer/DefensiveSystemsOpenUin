#pragma once
#include <algorithm>
#include <string>


#include "../../../Utils/Headers/Serialize.h"


#include "UserRegistrationPayload.h"

class UserRegistrationRequest : public Request<RequestCode::user_registration, UserRegistrationPayload> {
public:
    UserRegistrationRequest(const std::string& user_name) : Request() {
        std::copy(user_name.begin(), user_name.end(), this->payload_.user_name.begin());
    };
};

inline std::ostream& operator <<=(std::ostream& out, UserRegistrationPayload const& user_registration_payload) {
    out <<= user_registration_payload.user_name;
    return out;
}
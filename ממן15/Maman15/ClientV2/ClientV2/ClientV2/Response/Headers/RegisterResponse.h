#pragma once

#include "../../Utils/Headers/Constants.h"
#include "../../Utils/Headers/Serialize.h"

struct RegisterSuccessPayload {
	client_id client_id;
};

inline std::istream& operator >>=(std::istream& in, RegisterSuccessPayload& payload) {
	in >>= payload.client_id;
	return in;
}
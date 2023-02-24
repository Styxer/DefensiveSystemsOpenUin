#pragma once

#include "Constants.h"

struct crc_request_payload {
	client_id client_id{};
	filename filename{};
};
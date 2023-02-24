#pragma once
#include <cstdint>

#include "Constants.h"

struct FileUploadPayload {
	client_id client_id;
	uint32_t content_size;
	filename filename;
	// Encrypted content will be sent by the user class
};

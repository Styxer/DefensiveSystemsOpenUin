#pragma once

#include "../../../Utils/Headers/Constants.h"

struct FileUploadPayload {
	client_id client_id;
	uint32_t content_size;
	file_name file_name;
};


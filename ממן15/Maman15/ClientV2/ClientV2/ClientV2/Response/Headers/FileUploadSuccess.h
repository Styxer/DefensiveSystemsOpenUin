#pragma once
#include <array>

#include "../../Utils/Headers/Constants.h"
#include "../../Utils/Headers/Serialize.h"

struct FileUploadSuccessPayload {
	client_id client_id;
	uint32_t content_size;
	file_name file_name;
	uint32_t checksum;
};

inline std::istream& operator >>=(std::istream& in, FileUploadSuccessPayload& payload) {
	in >>= payload.client_id;
	in >>= payload.content_size;
	in >>= payload.file_name;
	in >>= payload.checksum;
	return in;
}
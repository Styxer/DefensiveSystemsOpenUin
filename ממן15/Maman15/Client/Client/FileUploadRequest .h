#pragma once
#include "AESHandler.h"
#include "FileUploadPayload .h"
#include "Request .h"
#include "Constants.h"
#include "serialize.h"

class FileUploadRequest : public Request<RequestCode::file_upload, FileUploadPayload> {
public:
    FileUploadRequest(const client_id &client_id, const std::string& filename, const uint32_t content_size) : Request(client_id) {
        std::copy(filename.begin(), filename.end(), this->payload_.file_name.begin());
        std::copy(client_id.begin(), client_id.end(), this->payload_.client_id.begin());
        this->payload_.content_size = content_size;
    }
};

inline std::ostream& operator <<=(std::ostream& out, FileUploadPayload const& payload) {
    out <<= payload.client_id;
    out <<= payload.content_size;
    out <<= payload.file_name;
    return out;
}

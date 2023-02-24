#pragma once
#include "AESHandler.h"
#include "FileUploadPayload .h"
#include "Request .h"
#include "Constants.h"

class FileUploadRequest : public Request<RequestCode::file_upload, FileUploadPayload> {
public:
    FileUploadRequest(const client_id &clientID, const std::string& filename, const uint32_t content_size) : Request(clientID) {
        std::copy(filename.begin(), filename.end(), this->payload_.filename.begin());
        std::copy(clientID.begin(), clientID.end(), this->payload_.client_id.begin());
        this->payload_.content_size = content_size;
    }
};

inline std::ostream& operator <<=(std::ostream& out, FileUploadPayload const& payload) {
    out <<= payload.client_id;
    out <<= payload.content_size;
    out <<= payload.filename;
    return out;
}

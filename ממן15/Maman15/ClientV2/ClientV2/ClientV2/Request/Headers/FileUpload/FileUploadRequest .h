#pragma once
#include <algorithm>
#include <string>

#include "FileUploadPayload.h"
#include "../../../Utils/Headers/Constants.h"
#include "../../../Utils/Headers/Serialize.h"


class FileUploadRequest : public Request<RequestCode::FILE_UPLOAD, FileUploadPayload> {
public:
    FileUploadRequest(const client_id& client_id, const std::string& filename, uint32_t content_size) : Request(client_id) {
        std::copy(filename.begin(), filename.end(), this->payload_.filename.begin());
        std::copy(client_id.begin(), client_id.end(), this->payload_.clientID.begin());
        this->payload_.contentSize = content_size;
    }
};

inline std::ostream& operator <<=(std::ostream& out, FileUploadPayload const& payload) {
    out <<= payload.client_id;
    out <<= payload.content_size;
    out <<= payload.file_name;
    return out;
}

#include <cstdint>
#include "Request.h"
#include "ServerLogic.h"


struct Response {
	const uint8_t version;
	uint16_t status;
	uint16_t nameLen;
	uint8_t* fileName;
	Payload payload;
	Response() : version(SERVER_VERSION), status(0), nameLen(0), fileName(nullptr){}

	uint32_t sizeWithPayload() const {
		return (sizeof(version) + sizeof(status) + sizeof(nameLen) + nameLen + sizeof(payload.size));
	}
};
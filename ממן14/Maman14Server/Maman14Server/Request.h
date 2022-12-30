#pragma once
#include <cstdint>
#include "SocketHandler.h"
struct Payload
{
	uint32_t size;
	uint8_t* payload;
	Payload() : size(0), payload(nullptr) {}
};

struct Request
{
#pragma pack(push,1)
	struct RequestHeader
	{
		uint32_t userId;
		uint8_t version;
		uint8_t op;

		RequestHeader() : userId(0), version(0), op(0) {}
	};
#pragma pack(pop)

	

	RequestHeader header;
	uint16_t nameLen; // file name length
	uint8_t* filename;
	Payload payload;
	Request() : nameLen(0), filename(nullptr) {}
	uint32_t sizeWithPayload() const {
		return (sizeof(header) + sizeof(nameLen) + nameLen + sizeof(payload.size));
	}

};//end Request struct

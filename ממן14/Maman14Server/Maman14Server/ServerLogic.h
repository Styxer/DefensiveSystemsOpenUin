#pragma once
#include "SocketHandler.h"
#include "FileHandler.h"
#include "Request.h"
#include "Response.h"
#include <map>
#include <atomic>
#include <boost/asio/ip/tcp.hpp>

class ServerLogic {
public:
	
	static const int SERVER_VERSION = 1;

#define BACKUP_FOLDER "c:/backup"

	struct Payload  // Common for Request & Response.
	{
		uint32_t size;     // payload size
		uint8_t* payload;
		Payload() : size(0), payload(nullptr) {}
	};

	struct Request
	{
#pragma pack(push,1)
		struct RequestHeader
		{
			uint32_t userId;     // User ID
			uint8_t  version;    // Client Version
			uint8_t  op;         // Request Code
			RequestHeader() : userId(0), version(0), op(0) {}
		};
#pragma pack(pop)
		RequestHeader header;
		uint16_t nameLen; // file name length
		uint8_t* fileName;
		Payload payload;
		Request() : nameLen(0), fileName(nullptr) {}
		uint32_t getSizeWithPayload() const {
			return (sizeof(header) + sizeof(nameLen) + nameLen + sizeof(payload.size));
		}

	};//end Request struct

private:
	FileHandler _fileHandler;
	SocketHandler _socketHandler;
	std::map<uint32_t, std::atomic<bool>> _userHandling;

	std::string createRandomString(const uint32_t lenght) const;
	bool userHadFiles(const uint32_t userId);
	bool parseFileName(const uint16_t fileNameLength, const uint8_t* fileName, std::string& parsedFileName);
	void copyFileName(const Request& request, Response& response);
	bool handleRequest(const Request& request, Response*& response, bool& responseSent, boost::asio::ip::tcp::socket& socket);
	Request* deserializeRequest(const uint8_t* const buffer, const uint32_t size);
	void serializeResponse(const Response& response, uint8_t* buffer);
	void release(uint8_t* ptr);
	void release(Request* request);
	void release(Response* response);
	bool lock(const Request& request);
	void unlock(const Request& request);
	 
public:
	bool handleSocketFromThread(boost::asio::ip::tcp::socket& socket);

};


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
#define SERVER_VERSION 1.0
#define BACKUP_FOLDER "c:/backup"

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

private:
	FileHandler _fileHandler;
	SocketHandler _socketHandler;
	std::map<uint32_t, std::atomic<bool>> _userHandling;

	std::string randString(const uint32_t lenght) const;
	bool userHadFile(const uint32_t userId);
	bool parseFileName(const uint16_t fileNameLength, const uint8_t* fileName, std::string& parsedFileName);
	void copyFileName(const Request& request, Response& response);
	bool handleRequest(const Request& request, Response*& response, bool& responseSent, boost::asio::ip::tcp::socket& socket, std::stringstream& error);
	Request* desrializeRequest(const uint8_t* const buffer, const uint32_t size);
	void serializeReponse(const Response& response, uint8_t buffer);
	void destory(uint8_t* ptr);
	void destroy(Request* request);
	void destroy(Response* response);
	bool lock(const Request& request);
	void unlock(const Request& request);
	 
public:
	bool handleSocketFromThread(boost::asio::ip::tcp::socket& socket, std::stringstream& error);

};


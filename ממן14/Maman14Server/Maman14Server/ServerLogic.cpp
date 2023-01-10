#include "ServerLogic.h"
#include <sstream>
#include <algorithm>
#include <fstream>
#include <thread>
#include <random>
#include <iostream>
#include "StatusEnum.h"
#include "OPEnum.h"

/// <summary>
/// genrate a random string based on a given length
/// </summary>
/// <param name="length">string length</param>
/// <returns>the genreated string</returns>
/// 
/// based on answer from https://stackoverflow.com/questions/47977829/generate-a-random-string-in-c11
std::string ServerLogic::createRandomString(const uint32_t length)
{
	std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

	std::random_device rd;
	std::mt19937 generator(rd());

	std::shuffle(str.begin(), str.end(), generator);

	return str.substr(0, length);
}

/// <summary>
/// checks if a user has any files
/// </summary>
/// <param name="userId">the user id</param>
/// <returns>true if the user has any files.flase otherwise</returns>
bool ServerLogic::userHadFiles(const uint32_t userId) const
{
	if (userId == 0) return false;

	std::stringstream stringStream;

	stringStream << BACKUP_FOLDER <<  "/" << userId;
	const auto userBackupFolder = stringStream.str();
	std::set<std::string> userFiles;

	if (!_fileHandler.getFileList(userBackupFolder, userFiles)) return false;

	return !userFiles.empty();
}

/// <summary>
/// try to parse the file name as array of bytes
/// </summary>
/// <param name="fileNameLength">the lenght of the given file name</param>
/// <param name="fileName">the given file name as array of bytes</param>
/// <param name="parsedFileName">parsed file as string from file name</param>
/// <returns>true if file name was parsed successfully. false otherwise</returns>
bool ServerLogic::parseFileName(const uint16_t fileNameLength, const uint8_t* fileName, std::string& parsedFileName)
{
	if (fileNameLength == 0 || fileNameLength > FILENAME_MAX || fileName == nullptr) return false;

	try
	{
		const auto str = new char[fileNameLength + 1];
		memcpy(str, fileName, fileNameLength);
		str[fileNameLength] = '\0';
		parsedFileName = str;
		delete[] str;
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return false;
	}
	return true;
}

/// <summary>
/// copies the file name from the request to the response
/// </summary>
/// <param name="request">the source of the file name</param>
/// <param name="response">the destionation for the file name</param>
void ServerLogic::copyFileName(const Request& request, Response& response)
{
	if (request.nameLen == 0) return;

	try
	{
		response.nameLen = request.nameLen;
		response.fileName = new uint8_t[request.nameLen];
		memcpy(response.fileName, request.fileName, request.nameLen);
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
}

/// <summary>
/// Hand;e the client rquest
/// </summary>
/// <param name="request">the quest to be handled</param>
/// <param name="response">the resposne to the request</param>
/// <param name="responseSent">the response to the request that was sent to the server</param>
/// <param name="socket">the connected socket</param>
/// <returns>true if no error occurred.false otherwise</returns>
bool ServerLogic::handleRequest(const Request& request, Response*& response, bool& responseSent, boost::asio::ip::tcp::socket& socket)
{
	responseSent = false;
	response = new Response();

	if (request.header.userId == 0)
	{
		std::cerr << "User ID #" << +request.header.userId << +"is not valid" << std::endl;
		response->status = StatusEnum::ERROR_GENERIC;
		return false;
	}
	//  validation for FILE_RESTORE | FILE_REMOVE | FILE_DIR requests.
	if ((request.header.op & (OPEnum::FILE_RESTORE | OPEnum::FILE_REMOVE | OPEnum::FILE_DIR)) == request.header.op)
	{
		if (!userHadFiles(request.header.userId))
		{
			std::cerr << "Error :Request from user ID #" << +request.header.userId << +" has no files" << std::endl;
			response->status = StatusEnum::ERROR_NO_FILES;
			return false;
		}
	}
	// validation for FILE_BACKUP | FILE_RESTORE | FILE_REMOVE requests.
	std::string parsedFileName;
	if ((request.header.op & (OPEnum::FILE_BACKUP | OPEnum::FILE_RESTORE | OPEnum::FILE_REMOVE)) == request.header.op)
	{
		if (!parseFileName(request.nameLen, request.fileName, parsedFileName))
		{
			std::cerr << "Error : Request  from user ID #" << +request.header.userId << ": Invalid filename!" << std::endl;
			response->status = StatusEnum::ERROR_GENERIC;
			return false;
		}
		copyFileName(request, *response);
	}

	std::stringstream userPathStream, filepathStream;
	userPathStream << BACKUP_FOLDER <<  "/" << request.header.userId << "/";
	filepathStream << userPathStream.str() << parsedFileName;
	const std::string filepath = filepathStream.str();
	//  validation for FILE_RESTORE | FILE_REMOVE requests.
	if ((request.header.op & (OPEnum::FILE_RESTORE | OPEnum::FILE_REMOVE)) == request.header.op)
	{
		if (!_fileHandler.isFileExists(filepath))
		{
			std::cerr << "Error :Request  for user ID #" << +request.header.userId << ": File not exists!" << std::endl;
			response->status = StatusEnum::ERROR_NOT_EXIST;
			return false;
		}
	}

	response->status = StatusEnum::ERROR_GENERIC;//set default status
	uint8_t buffer[PACKET_SIZE];
	switch (request.header.op)
	{
		case OPEnum::FILE_BACKUP:
		{
			std::fstream fs;
			if (!_fileHandler.OpenFile(filepath, fs, FileWorkModeEnum::Write))
			{
				std::cerr << "Error: user ID #" << +request.header.userId << ": File " << parsedFileName << " failed to open." << std::endl;
				return false;
			}
			uint32_t bytes = (PACKET_SIZE - request.getSizeWithPayload());
			if (request.payload.size < bytes)
				bytes = request.payload.size;
			if (!_fileHandler.WriteFile(fs, request.payload.payload, bytes))
			{
				std::cerr << "Error: user ID #" << +request.header.userId << ": Write to file " << parsedFileName << " failed." << std::endl;
				fs.close();
				return false;
			}

			while (bytes < request.payload.size)
			{
				if (!_socketHandler.receive(socket, buffer))
				{
					std::cerr << "Error : user ID #" << +request.header.userId << ": receive file data from socket failed." << std::endl;
					fs.close();
					return false;
				}
				uint32_t length = PACKET_SIZE;
				if (bytes + PACKET_SIZE > request.payload.size)
					length = request.payload.size - bytes;
				if (!_fileHandler.WriteFile(fs, buffer, length))
				{
					std::cerr << "Error: user ID #" << +request.header.userId << ": Write to file " << parsedFileName << " failed." << std::endl;
					fs.close();
					return false;
				}
				bytes += length;
			}
			fs.close();
			response->status = StatusEnum::SUCCESS_BACKUP_DELETE;
			return true;
		}

		case OPEnum::FILE_RESTORE:
		{
			std::fstream fs;
			if (!_fileHandler.OpenFile(filepath, fs))
			{
				std::cerr << "Error: user ID #" << +request.header.userId << ": File " << parsedFileName << " failed to open." << std::endl;
				return false;
			}
			uint32_t fileSize = _fileHandler.fileSize(fs);
			if (fileSize == 0)
			{
				std::cerr << "Error:user ID #" << +request.header.userId << ": File " << parsedFileName << " has 0 zero." << std::endl;
				fs.close();
				return false;
			}
			response->payload.size = fileSize;
			uint32_t bytes = (PACKET_SIZE - response->sizeWithoutPayload());
			response->payload.payload = new uint8_t[bytes];
			if (!_fileHandler.ReadFile(fs, response->payload.payload, bytes))
			{
				std::cerr << "Error:user ID #" << +request.header.userId << ": File " << parsedFileName << " reading failed." << std::endl;
				fs.close();
				return false;
			}
			responseSent = true;
			response->status = StatusEnum::SUCCESS_RESTORE;
			serializeResponse(*response, buffer);
			if (!_socketHandler.send(socket, buffer))
			{
				std::cerr << "Error:Response sending on socket failed! user ID #" << +request.header.userId << std::endl;
				fs.close();
				socket.close();
				return false;
			}
			while (bytes < fileSize)
			{
				if (!_fileHandler.ReadFile(fs, buffer, PACKET_SIZE) || !_socketHandler.send(socket, buffer))
				{
					std::cerr << "Error:Payload data failure for user ID #" << +request.header.userId << std::endl;
					fs.close();
					socket.close();
					return false;
				}
				bytes += PACKET_SIZE;
			}
			release(response);
			fs.close();
			socket.close();
			return true;
		}

		case OPEnum::FILE_REMOVE:
		{
			if (!_fileHandler.RemoveFile(filepath))
			{
				std::cerr << "Error:Request Error for user ID #" << +request.header.userId << ": File deletion failed!" << std::endl;
				return false;
			}
			response->status = StatusEnum::SUCCESS_BACKUP_DELETE;
			return true;
		}

		case OPEnum::FILE_DIR:
		{
			std::set<std::string> userFiles;
			std::string userFolder(userPathStream.str());
			if (!_fileHandler.getFileList(userFolder, userFiles))
			{
				std::cerr << "Error:Request Error for user ID #" << +request.header.userId << ": FILE_DIR generic failure." << std::endl;
				response->status = StatusEnum::ERROR_GENERIC;
				return false;		
			}
			constexpr size_t filename_len = 32;
			response->fileName = new uint8_t[filename_len];
			response->nameLen = filename_len;
			memcpy(response->fileName, createRandomString(filename_len).c_str(), filename_len);
			response->status = StatusEnum::SUCCESS_DIR;

			uint32_t listSize = 0;
			for (const auto& userFile : userFiles)
			{
				listSize += userFile.size() + 1;
			}
			response->payload.size = listSize;
			auto const list_ptr = new uint8_t[listSize];
			auto ptr = list_ptr;
			for (const auto& userFile : userFiles)
			{
				memcpy(ptr, userFile.c_str(), userFile.size());
				ptr += userFile.size();
				*ptr = '\n';
				ptr += 1;
			}
			//// if file names do not exceed PACKET_SIZE.
			if (response->sizeWithoutPayload() + listSize <= PACKET_SIZE)
			{
				response->payload.payload = list_ptr;
				return true;
			}
			//else split message into smaller chuncks
			ptr = list_ptr;
			responseSent = true;  
			uint32_t remainingBytes = PACKET_SIZE - response->sizeWithoutPayload(); 
			response->payload.payload = new uint8_t[remainingBytes];
			memcpy(response->payload.payload, ptr, remainingBytes);
			ptr += remainingBytes;
			serializeResponse(*response, buffer);
			if (!_socketHandler.send(socket, buffer))
			{
				std::cerr << "Error:Response sending on socket failed! user ID #" << +request.header.userId << std::endl;
				release (response);
				socket.close();
				return false;
			}
			remainingBytes = PACKET_SIZE;
			while (remainingBytes < (response->sizeWithoutPayload() + listSize))
			{
				memcpy(buffer, ptr, PACKET_SIZE);
				ptr += PACKET_SIZE;
				remainingBytes += PACKET_SIZE;
				if (!_socketHandler.send(socket, buffer))
				{
					std::cerr << "Error:Payload data failure for user ID #" << +request.header.userId << std::endl;
					release(response);
					socket.close();
					return false;
				}
				release(response);
				socket.close();
				return true;
			}
		}
		default:
		{
			std::cerr << "Error: Request  for user ID #" << +request.header.userId << ": Invalid request code: " << +request.header.op << std::endl;
			return true;
		}
	}
}

/// <summary>
/// deserialize raw data into request.
/// </summary>
/// <param name="buffer">buffer of the data</param>
/// <param name="size">size of the data</param>
/// <returns>a Request</returns>
ServerLogic::Request* ServerLogic::deserializeRequest(const uint8_t* const buffer, const uint32_t size)
{
	uint32_t bytesToRead = 0;
	const uint8_t* ptr = buffer;
	if (size < sizeof(Request::RequestHeader))
	{
		std::cerr << "Error: invalid minimal size" << size << " is less then " << sizeof(Request::RequestHeader) << std::endl;
		return nullptr;
	}
	//create new request and fill the header
	auto const request = new Request;
	memcpy(request, ptr, sizeof(Request::RequestHeader));
	bytesToRead += sizeof(Request::RequestHeader);
	ptr += sizeof(Request::RequestHeader);
	if (bytesToRead + sizeof(uint16_t) > size)
		return request; 
	 
	// Copy name length
	memcpy(&(request->nameLen), ptr, sizeof(uint16_t));
	bytesToRead += sizeof(uint16_t);
	ptr += sizeof(uint16_t);
	if ((request->nameLen == 0) || ((bytesToRead + request->nameLen) > size))
	{
		std::cerr << " name length invalid" << std::endl;
		return request;
	}

	request->fileName = new uint8_t[request->nameLen + 1];
	memcpy(request->fileName, ptr, request->nameLen);
	request->fileName[request->nameLen] = '\0';
	bytesToRead += request->nameLen;
	ptr += request->nameLen;

	if (bytesToRead + sizeof(uint16_t) > size)
		return request;

	// copy payload size
	memcpy(&(request->payload.size), ptr, sizeof(uint32_t));
	bytesToRead += sizeof(uint32_t);
	ptr += sizeof(uint32_t);
	if (request->payload.size == 0)
	{
		std::cerr << "name length invalid." << std::endl;
		return request; 
	}

	// copy payload until size limit.
	uint32_t sizeRemains = size - bytesToRead;
	if (request->payload.size < sizeRemains)
		sizeRemains = request->payload.size;
	request->payload.payload = new uint8_t[sizeRemains];
	memcpy(request->payload.payload, ptr, sizeRemains);

	return request;
		
}

/// <summary>
/// serialize response to raw data
/// </summary>
/// <param name="response">a response param>
/// <param name="buffer">the buffer data</param>
void ServerLogic::serializeResponse(const Response& response, uint8_t* buffer)
{
	uint8_t* ptr = buffer;
	uint32_t size = (PACKET_SIZE - response.sizeWithoutPayload());
	if (response.payload.size < size)
		size = response.payload.size;

	//copy the memory of all response properties to buffer
	memcpy(ptr, &(response.version), sizeof(response.version));
	ptr += sizeof(response.version);
	memcpy(ptr, &(response.status), sizeof(response.status));
	ptr += sizeof(response.status);
	memcpy(ptr, &(response.nameLen), sizeof(response.nameLen));
	ptr += sizeof(response.nameLen);
	memcpy(ptr, (response.fileName), response.nameLen);
	ptr += response.nameLen;
	memcpy(ptr, &(response.payload.size), sizeof(response.payload.size));
	ptr += sizeof(response.payload.size);
	memcpy(ptr, (response.payload.payload), size);
}


/// <summary>
/// releases the memory 
/// </summary>
/// <param name="ptr">the ptr</param>
/// 
void ServerLogic::release(const uint8_t* ptr)
{
	if (ptr != nullptr)
	{
		delete[] ptr;
		ptr = nullptr;
	}
}

/// <summary>
/// releases the memory of the sent request
/// </summary>
/// <param name="request">the request</param>
void ServerLogic::release(const Request* request) const
{
	if (request != nullptr)
	{
		release(request->fileName);
		release(request->payload.payload);
		delete request;
		request = nullptr;
	}
}

/// <summary>
/// release the memorey of current response
/// </summary>
/// <param name="response">current response</param>
void ServerLogic::release(const Response* response) const
{
	if (response != nullptr)
	{
		release(response->fileName);
		release(response->payload.payload);
		delete response;
		response = nullptr;
	}
}

/// <summary>
/// locks the current request
/// </summary>
/// <param name="request">the current request</param>
/// <returns>true if lock succeded. false otherwise</returns>
bool ServerLogic::lock(const Request& request)
{
	if (request.header.userId == 0)
		return true;
	if (_userHandling[request.header.userId])
		return false;
	_userHandling[request.header.userId] = true;
	return true;
}

/// <summary>
/// unlock the request
/// </summary>
/// <param name="request">the reuqest to be unlocked</param>
void ServerLogic::unlock(const Request& request)
{
	if (request.header.userId == 0)
		return;
	_userHandling[request.header.userId] = false;
}

/// <summary>
/// handle socket at thread
/// </summary>
/// <param name="socket">the socket that the client is connect to</param>
/// <returns>true if success.false otherwise</returns>
bool ServerLogic::handleSocketFromThread(boost::asio::ip::tcp::socket& socket)
{
	try
	{
		uint8_t buffer[PACKET_SIZE];
		Response* response;
		bool responseSent;

		if (!_socketHandler.receive(socket, buffer))
		{
			std::cerr << "ServerLogic::handleRequest--> failed to get message from socket" << std::endl;
			return false;
		}

		const Request* request = deserializeRequest(buffer, PACKET_SIZE);
		while (!lock(*request)) //if server is busy with the same user
		{
			std::this_thread::sleep_for(std::chrono::seconds(5)); //TODO: change to more "normal" busy-wait pattern
		}
		const bool isSuccess = handleRequest(*request, response, responseSent, socket);

		if (!responseSent)
		{
			serializeResponse(*response, buffer);
			if (!_socketHandler.send(socket, buffer))
			{
				std::cerr << "ServerLogic::handleRequest--> send response failed" << std::endl;
				release(response);
				return false;
			}
			release(response);
			socket.close();
		}

		unlock(*request);
		release(request);

		return isSuccess;
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return false;
	}
}
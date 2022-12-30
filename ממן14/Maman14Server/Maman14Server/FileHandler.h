#pragma once
#include <set>
#include <string>

class FileHandler {
public:
	bool OpenFile(const std::string& filePath, std::fstream& fs, bool write = false);
	bool CloseFile(std::fstream& fs);
	bool WriteFile(std::fstream& fs, const uint8_t* const file, const uint32_t bytes);
	bool ReadFile(std::fstream& fs, uint8_t* const file, uint32_t bytes);
	uint32_t fileSize(std::fstream& fs);

	bool getFileList(std::string& filePath, std::set<std::string>& fileList);
	bool isFileExists(const std::string& filePath);
	bool RemoveFile(const std::string& filePath);
};
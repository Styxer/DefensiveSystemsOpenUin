#pragma once
#include <set>
#include <string>
#include "FileWorkModeEnum.h"

class FileHandler {
public:
	bool OpenFile(const std::string& filePath, std::fstream& fs, FileWorkModeEnum write = FileWorkModeEnum::Read) const;
	static bool CloseFile(std::fstream& fs);
	static bool WriteFile(std::fstream& fs, const uint8_t* const file, const uint32_t bytes);
	static bool ReadFile(std::fstream& fs, uint8_t* const file, uint32_t bytes);
	static uint32_t fileSize(std::fstream& fs);

	bool getFileList(const std::string& filePath, std::set<std::string>& fileList) const;
	static bool isFileExists(const std::string& filePath);
	bool RemoveFile(const std::string& filePath) const;
};
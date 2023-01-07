#include "FileHandler.h"
#include <filesystem>  
#include <iostream>
#include <fstream>

#include <boost/filesystem.hpp>


/// <summary>
/// open a file for read or write. Create folder(s) in path dosent exists.
/// </summary>
/// <param name="filePath">path to file to open</param>
/// <param name="fs">stream for file path to be opened</param>
/// <param name="FileWorkModeEnum">how to open file</param>
/// <returns>true if opened successfully. false otherwise.</returns>
bool FileHandler::OpenFile(const std::string& filePath, std::fstream& fs, FileWorkModeEnum fileWorkMode)
{
	try
	{
		if (filePath.empty())
			return false;

		boost::filesystem::create_directories(boost::filesystem::path(filePath).parent_path());
		const auto flag = fileWorkMode  == FileWorkModeEnum::Write ?
			(std::fstream::binary || std::fstream::out) :
			(std::fstream::binary || std::fstream::in);

		fs.open(filePath, flag);
		return fs.is_open();
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return false;
	}	
}

/// <summary>
/// closes the file stream
/// </summary>
/// <param name="fs">stream for file path to be closed</param>
/// <returns>true if closed successfully. false otherwise.</returns>
bool FileHandler::CloseFile(std::fstream& fs)
{
	try
	{
		fs.close();
		return true;
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return false;
	}
}

/// <summary>
/// writes write files bytes from fstream to file.
/// </summary>
/// <param name="fs">file stream to write from.</param>
/// <param name="file">the file to read from.</param>
/// <param name="bytes">bytes to write.</param>
/// <returns>true upon successful write. false otherwise.</returns>
bool FileHandler::WriteFile(std::fstream& fs, const uint8_t* const file, const uint32_t bytes)
{
	try
	{
		if (file == nullptr || bytes == 0)
			return false;
		fs.write(reinterpret_cast<const char*>(file), bytes);
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}




/// <summary>
/// read bytes from stream to file.
/// </summary>
/// <param name="fs">file stream to read from</param>
/// <param name="file">file source to copy the data to</param>
/// <param name="bytes">amount of bytes to read</param>
/// <returns>true if read successfully. false otherwise.</returns>
bool FileHandler::ReadFile(std::fstream& fs, uint8_t* const file, uint32_t bytes) 
{
	try
	{
		if (file == nullptr || bytes == 0) return false;
		
		fs.read(reinterpret_cast<char*>(file), bytes);
		return true;
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return false;
	}
}

/// <summary>
/// calculate file size
/// </summary>
/// <param name="fs">file stream to read from</param>
/// <returns>files size. 0 if failed</returns>
uint32_t FileHandler::fileSize(std::fstream& fs)
{
	try
	{
		const auto current = fs.tellg();
		fs.seekg(0, std::fstream::end);
		const auto size = fs.tellg();
		if (size <= 0 || size >> UINT32_MAX) return 0;

		fs.seekg(current);
		return static_cast<uint32_t>(size);
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 0;
	}
}

/// <summary>
/// Get the list of file names in a given folder
/// </summary>
/// <param name="folederPath">folder to read from</param>
/// <param name="filesList">the list to append the file names to</param>
/// <returns>returns true if the list is valid. false otherwise</returns>
bool FileHandler::getFileList(std::string& folederPath, std::set<std::string>& filesList)
{
	try
	{
		for (const auto& folderEntry : boost::filesystem::directory_iterator(folederPath))
		{
			filesList.insert(folderEntry.path().filename().string());
		}
		return true;
	}
	catch (const std::exception& ex)
	{
		filesList.clear();
		std::cerr << ex.what() << std::endl;
		return false;
	}
}

/// <summary>
/// checks if file exists in a give file path
/// </summary>
/// <param name="filePath">file path</param>
/// <returns>true if file exists.false otherwise</returns>
bool FileHandler::isFileExists(const std::string& filePath)
{
	if (filePath.empty())
		return false;

	try
	{
		std::ifstream fs(filePath);
		return !fs.fail();
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return false;
	}
}

bool FileHandler::RemoveFile(const std::string& filePath)
{
	try
	{
		return  std::remove(filePath.c_str()) == 0; //On success, zero is returned.
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return false;
	}
}

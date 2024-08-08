#pragma once
#include <string>
#include <filesystem>

namespace File
{
	std::string GetFilePath();
	bool SetFilePath(const std::string filePath);
	bool FileExists(const std::string filePath);
	bool GetFileSize(const std::string filePath, int& size); // returns whether it succeeds and changes the int passed in to the file size

	bool ReadFile(const std::string filePath, std::string& buffer);
}
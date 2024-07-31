#pragma once
#include <string>
#include <filesystem>

namespace File
{
	std::string GetFilePath();
	bool SetFilePath(const std::string filePath);
}
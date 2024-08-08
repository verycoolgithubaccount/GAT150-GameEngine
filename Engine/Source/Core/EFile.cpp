#include "EFile.h"
#include <iostream>
#include <fstream>

std::string File::GetFilePath()
{
    return std::filesystem::current_path().string();
}

bool File::SetFilePath(const std::string filePath)
{
    std::error_code ec;
    std::filesystem::current_path(filePath, ec);

    return !ec;
}

bool File::FileExists(const std::string filePath)
{
    return std::filesystem::exists(filePath);
}

bool File::GetFileSize(const std::string filePath, int& size)
{
    std::error_code ec;
    size = (int)std::filesystem::file_size(filePath, ec);

    return !ec;
}

bool File::ReadFile(const std::string filePath, std::string& buffer)
{
    if (!FileExists(filePath))
    {
        std::cerr << "File does not exist: " << filePath << std::endl;
        return false;
    }

    std::ifstream istream(filePath);
    if (!istream.is_open())
    {
        std::cerr << "Could not open file: " << filePath << std::endl;
        return false;
    }

    std::ostringstream ostream;
    ostream << istream.rdbuf();

    buffer = ostream.str();

    return true;
}

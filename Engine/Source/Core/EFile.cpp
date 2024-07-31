#include "EFile.h"

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

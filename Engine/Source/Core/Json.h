#pragma once

#include <rapidjson/document.h>
#include <string>

#define READ_DATA(value, data) Json::Read(value, #data, data) // if the key name is the same as the variable name, automatically uses the variable name for it

namespace Json
{
	bool Load(const std::string& filename, rapidjson::Document& document);
	bool Read(const rapidjson::Value& value, const std::string& key, int& data);
	bool Read(const rapidjson::Value& value, const std::string& key, bool& data);
	bool Read(const rapidjson::Value& value, const std::string& key, std::string& data);
}
#pragma once
#include "Math/Vector2.h"
#include "Math/Rect.h"
#include "Renderer/Color.h"

#include <rapidjson/document.h>
#include <string>
#include <vector>

#define READ_DATA(value, data) Json::Read(value, #data, data) // if the key name is the same as the variable name, automatically uses the variable name for it
#define READ_DATA_REQUIRED(value, data) Json::Read(value, #data, data, true)
#define READ_DATA_NAME(value, name, data) Json::Read(value, name, data) // This is entirely unnecessary but looks prettier
#define READ_DATA_NAME_REQUIRED(value, name, data) Json::Read(value, name, data, true) // This is entirely unnecessary but looks prettier
#define READ_DATA_STRUCT(value, data, _struct) Json::Read(value, #data, _struct.##data)

#define HAS_DATA(value, data) value.HasMember(#data)
#define GET_DATA(value, data) value[#data]

using json_t = rapidjson::Value;
// typedef rapidjson::Value json_t; also works but isn't as readable

namespace Json
{
	bool Load(const std::string& filename, rapidjson::Document& document);
	bool Read(const json_t& value, const std::string& key, int& data, bool isRequired = false);
	bool Read(const json_t& value, const std::string& key, float& data, bool isRequired = false);
	bool Read(const json_t& value, const std::string& key, bool& data, bool isRequired = false);
	bool Read(const json_t& value, const std::string& key, std::string& data, bool isRequired = false);
	bool Read(const json_t& value, const std::string& key, Color& data, bool isRequired = false);
	bool Read(const json_t& value, const std::string& key, Vector2& data, bool isRequired = false);
	bool Read(const json_t& value, const std::string& key, Rect& data, bool isRequired = false);
	bool Read(const json_t& value, const std::string& key, std::vector<int>& data, bool isRequired = false);
	bool Read(const json_t& value, const std::string& key, std::vector<std::string>& data, bool isRequired = false);
}


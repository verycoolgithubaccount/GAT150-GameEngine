#pragma once
#include "Math/Vector2.h"
#include "Renderer/Color.h"

#include <rapidjson/document.h>
#include <string>

#define READ_DATA(value, data) Json::Read(value, #data, data) // if the key name is the same as the variable name, automatically uses the variable name for it
#define READ_DATA_REQUIRED(value, data) Json::Read(value, #data, data, true)

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
}


#include "Json.h"
#include "EFile.h"
#include <rapidjson/istreamwrapper.h>
#include <iostream>

namespace Json
{
	bool Load(const std::string& filename, rapidjson::Document& document)
	{
		std::string buffer;
		if (!File::ReadFile(filename, buffer)) return false;

		std::stringstream stream(buffer);
		rapidjson::IStreamWrapper istream(stream);

		document.ParseStream(istream);
		if (!document.IsObject())
		{
			std::cerr << "Could not parse Json: " << filename << std::endl;
			return false;
		}

		return true;
	}

	bool Read(const rapidjson::Value& value, const std::string& key, int& data) // int 
	{
		if (!value.HasMember(key.c_str()) || !value[key.c_str()].IsInt())
		{
			std::cerr << "Could not read json int value: " << key << std::endl;
			return false;
		}

		data = value[key.c_str()].GetInt();
		return true;
	}

	bool Read(const rapidjson::Value& value, const std::string& key, float& data)
	{
		if (!value.HasMember(key.c_str()) || !value[key.c_str()].IsNumber())
		{
			std::cerr << "Could not read json float value: " << key << std::endl;
			return false;
		}

		data = value[key.c_str()].GetFloat();
		return true;
	}

	bool Read(const rapidjson::Value& value, const std::string& key, bool& data) // bool
	{
		if (!value.HasMember(key.c_str()) || !value[key.c_str()].IsBool())
		{
			std::cerr << "Could not read json bool value: " << key << std::endl;
			return false;
		}

		data = value[key.c_str()].GetBool();
		return true;
	}

	bool Read(const rapidjson::Value& value, const std::string& key, std::string& data) // string
	{
		if (!value.HasMember(key.c_str()) || !value[key.c_str()].IsString())
		{
			std::cerr << "Could not read json string value: " << key << std::endl;
			return false;
		}

		data = value[key.c_str()].GetString();
		return true;
	}

	bool Read(const rapidjson::Value& value, const std::string& key, Color& data) // Color
	{
		if (!value.HasMember(key.c_str()) || !value[key.c_str()].IsArray() || value[key.c_str()].Size() != 4)
		{
			std::cerr << "Could not read Json value: " << key << std::endl;
			return false;
		}

		// get json array object
		auto& array = value[key.c_str()];
		// get array values
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				std::cerr << "Could not read Json value: " << key << std::endl;
				return false;
			}

			// get the data
			data[i] = array[i].GetFloat();
		}

		return true;
	}

	bool Read(const rapidjson::Value& value, const std::string& key, Vector2& data) // Vector2
	{
		if (!value.HasMember(key.c_str()) || !value[key.c_str()].IsArray() || value[key.c_str()].Size() != 2)
		{
			std::cerr << "Could not read Json value: " << key << std::endl;
			return false;
		}

		// get json array object
		auto& array = value[key.c_str()];
		// get array values
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				std::cerr << "Could not read Json value: " << key << std::endl;
				return false;
			}

			// get the data
			data[i] = array[i].GetFloat();
		}

		return true;
	}
}


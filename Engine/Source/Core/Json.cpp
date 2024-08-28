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

	bool Read(const json_t& value, const std::string& key, int& data, bool isRequired) // int 
	{
		if (!value.HasMember(key.c_str()) || !value[key.c_str()].IsInt())
		{
			if (isRequired) std::cerr << "Could not read json int value: " << key << std::endl;
			return false;
		}

		data = value[key.c_str()].GetInt();
		return true;
	}

	bool Read(const json_t& value, const std::string& key, float& data, bool isRequired) // float
	{
		if (!value.HasMember(key.c_str()) || !value[key.c_str()].IsNumber())
		{
			if (isRequired) std::cerr << "Could not read json float value: " << key << std::endl;
			return false;
		}

		data = value[key.c_str()].GetFloat();
		return true;
	}

	bool Read(const json_t& value, const std::string& key, bool& data, bool isRequired) // bool
	{
		if (!value.HasMember(key.c_str()) || !value[key.c_str()].IsBool())
		{
			if (isRequired) std::cerr << "Could not read json bool value: " << key << std::endl;
			return false;
		}

		data = value[key.c_str()].GetBool();
		return true;
	}

	bool Read(const json_t& value, const std::string& key, std::string& data, bool isRequired) // string
	{
		if (!value.HasMember(key.c_str()) || !value[key.c_str()].IsString())
		{
			if (isRequired) std::cerr << "Could not read json string value: " << key << std::endl;
			return false;
		}

		data = value[key.c_str()].GetString();
		return true;
	}

	bool Read(const json_t& value, const std::string& key, Color& data, bool isRequired) // Color
	{
		if (!value.HasMember(key.c_str()) || !value[key.c_str()].IsArray() || value[key.c_str()].Size() != 4)
		{
			if (isRequired) std::cerr << "Could not read Json Color value: " << key << std::endl;
			return false;
		}

		// get json array object
		auto& array = value[key.c_str()];
		// get array values
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				std::cerr << "Could not read Json value for Color: " << key << ", expected a number" << std::endl;
				return false;
			}

			// get the data
			data[i] = array[i].GetFloat();
		}

		return true;
	}

	bool Read(const json_t& value, const std::string& key, Vector2& data, bool isRequired) // Vector2
	{
		if (!value.HasMember(key.c_str()) || !value[key.c_str()].IsArray() || value[key.c_str()].Size() != 2)
		{
			if (isRequired) std::cerr << "Could not read Json Vector2 value: " << key << std::endl;
			return false;
		}

		// get json array object
		auto& array = value[key.c_str()];
		// get array values
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				std::cerr << "Could not read Json value for Vector2: " << key << ", expected a number" << std::endl;
				return false;
			}

			// get the data
			data[i] = array[i].GetFloat();
		}

		return true;
	}

	bool Read(const json_t& value, const std::string& key, Rect& data, bool isRequired)
	{
		if (!value.HasMember(key.c_str()) || !value[key.c_str()].IsArray() || value[key.c_str()].Size() != 4)
		{
			if (isRequired) std::cerr << "Could not read Json Rect value: " << key << std::endl;
			return false;
		}

		// get json array object
		auto& array = value[key.c_str()];

		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				std::cerr << "Could not read Json value for Rect: " << key << ", expected a number" << std::endl;
				return false;
			}
		}

		// get array values
		data.x = array[0].GetInt();
		data.y = array[1].GetInt();
		data.w = array[2].GetInt();
		data.h = array[3].GetInt();

		return true;
	}

	bool Read(const json_t& value, const std::string& key, std::vector<int>& data, bool isRequired)
	{
		if (!value.HasMember(key.c_str()) || !value[key.c_str()].IsArray())
		{
			if (isRequired) std::cerr << "Could not read Json Vector<Int> value: " << key << std::endl;
			return false;
		}

		// get json array object
		auto& array = value[key.c_str()];
		// get array values
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				std::cerr << "Could not read Json value for Vector<Int>: " << key << ", expected a number" << std::endl;
				return false;
			}

			// get the data
			data.push_back(array[i].GetInt());
		}

		return true;
	}

	bool Read(const json_t& value, const std::string& key, std::vector <std::string> & data, bool isRequired)
	{
		if (!value.HasMember(key.c_str()) || !value[key.c_str()].IsArray())
		{
			if (isRequired) std::cerr << "Could not read Json Vector<String> value: " << key << std::endl;
			return false;
		}

		// get json array object
		auto& array = value[key.c_str()];
		// get array values
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsString())
			{
				std::cerr << "Could not read Json value for Vector<String>: " << key << ", expected a string" << std::endl;
				return false;
			}

			// get the data
			data.push_back(array[i].GetString());
		}

		return true;
	}
}


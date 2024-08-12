#include "Object.h"

void Object::Read(const json_t& value)
{
	Json::Read(value, "name", m_name);
	Json::Read(value, "active", m_active);
}

void Object::Write(json_t& value)
{
	//
}
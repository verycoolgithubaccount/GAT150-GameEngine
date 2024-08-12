#include "Transform.h"

void Transform::Read(const json_t& value)
{
	READ_DATA(value, translation);
	READ_DATA(value, rotation);
	READ_DATA(value, scale);
}

void Transform::Write(json_t& value)
{
}

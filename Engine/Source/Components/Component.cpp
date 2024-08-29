#include "Component.h"

void Component::Read(const json_t& value)
{
	Object::Read(value);
	READ_DATA_NAME(value, "type", m_componentType); 
}

#pragma once
#include "Framework/Object.h"

class Component : public Object
{
protected:
	std::string m_componentType;
public:
	virtual void Update(float dt) = 0;
	class Actor* m_owner{ nullptr };

	void Read(const json_t& value);
	const std::string& GetComponentType() { return m_componentType; }
};
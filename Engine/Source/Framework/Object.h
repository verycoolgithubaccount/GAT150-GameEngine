#pragma once
#include <string>

class Object
{
protected:
	std::string m_name;
	bool m_active{ false };
public:
	Object() = default;
	Object(const std::string& name) : m_name{ name } {}

	virtual void Initialize() = 0;
	virtual void Activate() { m_active = true; }
	virtual void DeActivate() { m_active = false; }

	const std::string& GetName() const { return m_name; }
	bool isActive() const { return m_active; }

	void SetName(std::string name) { m_name = name; }
};
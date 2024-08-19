#pragma once
#include "Core/Serializable.h"
#include "Core/Factory.h"
#include <string>

#define CLASS_DECLARATION(classname) \
	static const char* GetTypeName() { return #classname; } \
	virtual void Read(const json_t& value);	\
	virtual void Write(json_t& value);

#define FACTORY_REGISTER(classname)									\
	class Register##classname										\
	{																\
	public:															\
		Register##classname()										\
		{															\
			Factory::Instance().Register<classname>(#classname);	\
		}															\
	};																\
	static Register##classname register_instance;

class Object : public Serializable
{
protected:
	std::string m_name;
	bool m_active{ true };
public:
	Object() = default;
	Object(const std::string& name) : m_name{ name } {}
	virtual ~Object() = default; // virtual makes sure that derived class destructor is also called in case there's code there, so everything is properly deleted

	CLASS_DECLARATION(Object);

	virtual void Initialize() = 0;
	virtual void Activate() { m_active = true; }
	virtual void DeActivate() { m_active = false; }

	const std::string& GetName() const { return m_name; }
	bool isActive() const { return m_active; }

	void SetName(std::string name) { m_name = name; }
};
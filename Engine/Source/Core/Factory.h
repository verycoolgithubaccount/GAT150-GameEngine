#pragma once
#include "Singleton.h"

#include <memory>
#include <map>
#include <iostream>

class CreatorBase
{
public:
	virtual ~CreatorBase() = default;
	virtual std::unique_ptr<class Object> Create() = 0;
};

template <typename T>
class Creator : public CreatorBase
{
public:
	std::unique_ptr<class Object> Create() override
	{
		return std::make_unique<T>();
	}
};

class Factory : public Singleton<Factory>
{
private:
	std::map<std::string, std::unique_ptr<class CreatorBase>> m_registry;
public:
	template<typename T> void Register(const std::string& key);
	template<typename T = class Object> std::unique_ptr<T> Create(const std::string& key);
	template<typename T> void RegisterPrototype(const std::string& name, std::unique_ptr<T> prototype);
};

template<typename T>
inline void Factory::Register(const std::string& key)
{
	// Add creator of type T to registry
	m_registry[key] = std::make_unique<Creator<T>>();
}

template<typename T>
inline std::unique_ptr<T> Factory::Create(const std::string& key)
{
	if (m_registry.find(key) != m_registry.end()) // if the key exists in the registry
	{
		// if in registry, run Create() for object of type T
		return std::unique_ptr<T>(dynamic_cast<T*>(m_registry[key]->Create().release()));
	}

	std::cerr << "Could not create factory object: " << key << std::endl;

	// name is not in registry, return unique ptr
	return std::unique_ptr<T>();
}

template<typename T>
class PrototypeCreator : public CreatorBase
{
private:
	std::unique_ptr<T> m_prototype;
public:
	PrototypeCreator(std::unique_ptr<T> prototype) : m_prototype{ std::move(prototype) } {}
	std::unique_ptr<class Object> Create() override
	{
		return m_prototype->Clone();
	}
};

template<typename T>
inline void Factory::RegisterPrototype(const std::string& name, std::unique_ptr<T> prototype)
{
	m_registry[name] = std::make_unique<PrototypeCreator<T>>(std::move(prototype));
}
#pragma once
#include <string>
#include <memory>
#include <cstdarg>

class Resource
{
public:
	Resource() = default;
	~Resource() = default;

	virtual bool Create(std::string name, ...) = 0; //... = variadic arguments, so you can pass in different types and numbers of params for different children
};

template<typename T = Resource> // Can be any class derived from this class
using res_t = std::shared_ptr<T>;
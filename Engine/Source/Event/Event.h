#pragma once
#include <string>
#include <variant>

using id_t = std::string;
using data_t = std::variant<int, bool, float, std::string>; 
// ^ makes a union with all the types you specify, so data_t can be any of the types in the std::variant

struct Event
{
	id_t id;
	data_t data;

	Event(const id_t& id, data_t data) : id{ id }, data{ data } {}
};
#pragma once
#include <string>
#include <algorithm>

std::string ToLower(const std::string& str); // needs to be const if you want to be able to pass string literals in addition to string variables
std::string ToUpper(const std::string& str); // needs to be const if you want to be able to pass string literals in addition to string variables

bool IsEqualIgnoreCase(const std::string& str1, const std::string& str2);
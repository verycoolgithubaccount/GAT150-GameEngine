#include "EString.h"

std::string ToLower(const std::string& str)
{
	std::string lower;
	lower.resize(str.size()); // Set the length of lower to the length of the original string

	//modern c++
	std::transform(str.begin(), str.end(), lower.begin(), // start of what to copy from, end of what to copy from, and what to start copying to
		[](char c) // what's in each vector to operate on 
		{
			return std::tolower(c); // how to transform the value when inputting it
		}
	);

	/*

	// Older c/c++
	for (int i = 0; i < str.size(); i++)
	{
		lower[i] = std::tolower(str[i]);
	}

	// This can use too much memory, reserve or resize should fix it but still
	for (auto c : str)
	{
		lower.push_back(std::tolower(c));
	}
	*/

	return lower;
}

std::string ToUpper(const std::string& str)
{
	std::string upper;
	upper.resize(str.size());

	//modern c++
	std::transform(str.begin(), str.end(), upper.begin(),
		[](char c)
		{
			return std::toupper(c);
		}
	);
	return upper;
}

bool IsEqualIgnoreCase(const std::string& str1, const std::string& str2)
{
	if (str1.length() != str2.length()) return false;

	// This is better than toLower(str1) == toLower(str2) because toLower creates a new string variable and...
	return std::equal(str1.begin(), str1.end(), str2.begin(),
		[](char c1, char c2)
		{
			//... because this returns false the moment one of the characters does not match so doesn't waste time
			return std::tolower(c1) == std::tolower(c2);
		}
	);
}

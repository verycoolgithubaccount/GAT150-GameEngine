#pragma once

template <typename T>
class Singleton
{
protected:
	Singleton() = default; 
public:
	// "= delete" disables default functions
	Singleton(const Singleton& other) = delete; // delete the copy constructor so a new variable can't be made from a singleton
	Singleton& operator = (const Singleton& other) = delete; // delete assignment operator which is basically the same as above

	static T& Instance()
	{
		static T instance; // "static" because static variables don't go out of scope so it won't be re-created every time this function is run
		return instance;
	}
};
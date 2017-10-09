#pragma once
#include "main.h"
//this is a class that has helper functions for dealing with strings
class StringUtils
{
public:
	StringUtils();
	~StringUtils();

	static std::string ConvertToString(std::wstring str);
	static std::wstring ConvertToWideString(std::string str);
private:
	template<typename From, typename To> static To ConvertString(From from)
	{
		To result = To(from.length(), 0);
		copy(from.begin(), from.end(), result.begin());
		return result;
	}
};


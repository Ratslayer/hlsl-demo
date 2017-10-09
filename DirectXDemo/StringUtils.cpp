#include "StringUtils.h"



StringUtils::StringUtils()
{
}


StringUtils::~StringUtils()
{
}

std::string StringUtils::ConvertToString(std::wstring str)
{
	std::string result = ConvertString<std::wstring, std::string>(str);
	return result;
}

std::wstring StringUtils::ConvertToWideString(std::string str)
{
	std::wstring result = ConvertString<std::string, std::wstring>(str);
	return result;
}

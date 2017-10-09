#pragma once
#include <exception>
#include <string>
#include <windows.h>
#include "StringUtils.h"
//This is a base exception class
class DxException :
	public std::exception
{
public:
	DxException(std::wstring msg);
	DxException(std::string msg);
	~DxException();

	void Display();
private:
	std::wstring message;
};
//common define for HRESULT checks
#define ASSERT_HR(hr, msg) if(FAILED(hr)) throw DxException(msg)


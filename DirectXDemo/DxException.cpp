#include "DxException.h"



DxException::DxException(std::wstring msg)
{
	message = msg;
}

DxException::DxException(std::string msg)
{
	message = StringUtils::ConvertToWideString(msg);
}


DxException::~DxException()
{
}
void DxException::Display()
{
	MessageBox(
		nullptr,
		message.c_str(), 
		L"DxException", 
		MB_OK);
}

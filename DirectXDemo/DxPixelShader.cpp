#include "DxPixelShader.h"



DxPixelShader::DxPixelShader()
	:DxShader()
{
	type = "PS";
	model = "ps_4_0";
}


DxPixelShader::~DxPixelShader()
{
}

void DxPixelShader::CreateShader(ComPtr<ID3DBlob> shaderData)
{
	DEVICE->CreatePixelShader(shaderData->GetBufferPointer(), shaderData->GetBufferSize(), nullptr, &shader);
}

void DxPixelShader::Apply()
{
	DxDevice::Instance()->Context->PSSetShader(shader.Get(), nullptr, 0);
}

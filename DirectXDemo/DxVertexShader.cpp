#include "DxVertexShader.h"



DxVertexShader::DxVertexShader()
	:DxShader()
{
	type = "VS";
	model = "vs_4_0";
}


DxVertexShader::~DxVertexShader()
{
}

void DxVertexShader::CreateShader(ComPtr<ID3DBlob> shaderData)
{
	DEVICE->CreateVertexShader(shaderData->GetBufferPointer(), shaderData->GetBufferSize(), nullptr, &shader);
	// Create the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);
	DEVICE->CreateInputLayout(
		layout, 
		numElements, 
		shaderData->GetBufferPointer(),
		shaderData->GetBufferSize(), 
		&VertexLayout);
}

void DxVertexShader::Apply()
{
	CONTEXT->IASetInputLayout(VertexLayout.Get());
	CONTEXT->VSSetShader(shader.Get(), nullptr, 0);
}

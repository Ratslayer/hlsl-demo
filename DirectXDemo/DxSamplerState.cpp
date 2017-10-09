#include "DxSamplerState.h"



DxSamplerState::DxSamplerState(D3D11_TEXTURE_ADDRESS_MODE mode)
{
	// Create the sample state
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = mode;
	sampDesc.AddressV = mode;
	sampDesc.AddressW = mode;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	HRESULT hr = DEVICE->CreateSamplerState(&sampDesc, &Sampler);
	if (FAILED(hr))
		throw DxException(L"Could not create sampler state.");
}


DxSamplerState::~DxSamplerState()
{
}

void DxSamplerState::Bind(int slot)
{
	CONTEXT->PSSetSamplers(slot, 1, Sampler.GetAddressOf());
}

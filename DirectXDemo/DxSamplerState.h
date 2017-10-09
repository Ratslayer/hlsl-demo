#pragma once
#include "main.h"
//wrapper class that helps with setting up sampler states
class DxSamplerState
{
public:
	DxSamplerState(D3D11_TEXTURE_ADDRESS_MODE mode);
	~DxSamplerState();

	ComPtr<ID3D11SamplerState> Sampler;
	void Bind(int slot = 0);
};


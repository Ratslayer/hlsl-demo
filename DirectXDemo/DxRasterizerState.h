#pragma once
#include "main.h"
//wrapper class that helps with setting up rasterizer states
class DxRasterizerState
{
public:
	DxRasterizerState();
	DxRasterizerState(D3D11_RASTERIZER_DESC desc);
	~DxRasterizerState();
	void Set();
private:
	ComPtr<ID3D11RasterizerState> _state;
};


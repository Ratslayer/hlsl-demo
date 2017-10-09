#pragma once
#include "DxTexture.h"
//this is a depth stencil target that can be used as a texture
class DxDepthStencil :
	public DxTexture
{
public:
	DxDepthStencil(UINT Width, UINT Height);
	~DxDepthStencil();

	virtual void Clear();
	ComPtr<ID3D11DepthStencilView> DepthStencilView;
};


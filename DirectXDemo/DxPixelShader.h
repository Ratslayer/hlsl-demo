#pragma once
#include "DxShader.h"
class DxPixelShader :
	public DxShader<ID3D11PixelShader>
{
public:
	DxPixelShader();
	~DxPixelShader();

	virtual void Apply();
protected:
	virtual void CreateShader(ComPtr<ID3DBlob> shaderData);
	
};


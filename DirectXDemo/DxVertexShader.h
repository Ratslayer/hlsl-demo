#pragma once
#include "DxShader.h"
class DxVertexShader :
	public DxShader<ID3D11VertexShader>
{
public:
	DxVertexShader();
	~DxVertexShader();

	ComPtr<ID3D11InputLayout> VertexLayout;
	virtual void Apply();
protected:
	virtual void CreateShader(ComPtr<ID3DBlob> shaderData);
	
};


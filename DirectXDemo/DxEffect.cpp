#include "DxEffect.h"

DxEffect::DxEffect( std::wstring fileName)
{
	VertexShader = LoadShader<DxVertexShader>(fileName);
	PixelShader = LoadShader<DxPixelShader>(fileName);
}

DxEffect::DxEffect(std::wstring vsFileName, std::wstring psFileName)
{
	VertexShader = LoadShader<DxVertexShader>(vsFileName);
	PixelShader = LoadShader<DxPixelShader>(psFileName);
}

DxEffect::~DxEffect()
{
}

void DxEffect::Apply()
{
	VertexShader->Apply();
	PixelShader->Apply();
}

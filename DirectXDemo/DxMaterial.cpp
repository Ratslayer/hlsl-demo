#include "DxMaterial.h"
DxMaterial::DxMaterial(std::wstring diffuseFileName, std::wstring normalFileName)
{
	Diffuse = std::shared_ptr<DxTexture>(new DxTexture(diffuseFileName));
	Normal = std::shared_ptr<DxTexture>(new DxTexture(normalFileName));
}

DxMaterial::~DxMaterial()
{
}

void DxMaterial::Bind()
{
	Diffuse->AttachToPSSlot(0);
	Normal->AttachToPSSlot(1);
}

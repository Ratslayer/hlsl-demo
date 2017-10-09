#pragma once
#include "DxTexture.h"
//this class contains all the textures and values needed to describe a material
class DxMaterial
{
public:
	DxMaterial(std::wstring diffuseFileName, std::wstring normalFileName);
	~DxMaterial();

	std::shared_ptr<DxTexture> Diffuse;
	std::shared_ptr<DxTexture> Normal;

	void Bind();
};


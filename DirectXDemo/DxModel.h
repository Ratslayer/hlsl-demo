#pragma once
#include "main.h"
#include "DxMesh.h"
#include "DxMaterial.h"
//wrapper class that binds mesh to material
//I don't like this, this should be refactored into DxObject
class DxModel
{
public:
	DxModel(std::shared_ptr<DxMaterial> material);
	~DxModel();

	std::shared_ptr<DxMesh> Mesh;			//object mesh
	std::shared_ptr<DxMaterial> Material;	//object material
	void Draw();
};


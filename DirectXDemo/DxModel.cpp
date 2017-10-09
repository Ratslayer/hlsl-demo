#include "DxModel.h"
#include "DxCube.h"


DxModel::DxModel(std::shared_ptr<DxMaterial> material)
{
	Material = material;
	Mesh = std::shared_ptr<DxMesh>(new DxCube());
}


DxModel::~DxModel()
{
}

void DxModel::Draw()
{
	Material->Bind();
	Mesh->Draw();
}

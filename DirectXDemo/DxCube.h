#pragma once
#include "DxModel.h"
//This class creates a cube mesh and computes its normals and tangents
class DxCube :
	public DxMesh
{
public:
	DxCube();
	~DxCube();

private:
	//calculate tangents from edges and tex coords
	void CalculateTangentArray(std::vector<DxMesh::MeshVertex> &vertices, std::vector<WORD> &indices);
};



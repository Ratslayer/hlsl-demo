#pragma once
#include "main.h"
//This is the base mesh class that contains all the data needed to store and draw any mesh
//TODO: add ability to load data from a .obj file
class DxMesh
{
public:
	//vertex format
	//this needs to always be in sync with the vertex input layout
	struct MeshVertex
	{
		XMFLOAT3 Pos;
		XMFLOAT2 Tex;
		XMFLOAT3 Normal;
		XMFLOAT3 Tangent;
	};

	DxMesh();
	~DxMesh();

	void Draw();
protected:
	void CreateBuffers(std::vector<MeshVertex> vertices, std::vector<WORD> indices);
private:
	int numIndices;
	ComPtr<ID3D11Buffer> VertexBuffer;
	ComPtr<ID3D11Buffer> IndexBuffer;
};


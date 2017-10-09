#include "DxModel.h"


DxMesh::DxMesh()
{
	
}

void DxMesh::CreateBuffers(std::vector<MeshVertex> vertices, std::vector<WORD> indices)
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(MeshVertex) * vertices.size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices.data();
	HRESULT hr = DEVICE->CreateBuffer(&bd, &InitData, &VertexBuffer);
	ASSERT_HR(hr, "Could not create vertex buffer.");

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * indices.size();
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = indices.data();
	hr = DEVICE->CreateBuffer(&bd, &InitData, &IndexBuffer);
	ASSERT_HR(hr, "Could not create index buffer.");

	numIndices = indices.size();
}


DxMesh::~DxMesh()
{
}

void DxMesh::Draw()
{
	// Set vertex buffer
	UINT stride = sizeof(MeshVertex);
	UINT offset = 0;
	CONTEXT->IASetVertexBuffers(0, 1, VertexBuffer.GetAddressOf(), &stride, &offset);

	// Set index buffer
	CONTEXT->IASetIndexBuffer(IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

	// Set primitive topology
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	CONTEXT->DrawIndexed(numIndices, 0, 0);
}

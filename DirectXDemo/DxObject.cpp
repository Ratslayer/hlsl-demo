#include "DxObject.h"



DxObject::DxObject(Vector3 pos, Vector3 scale, float angle)
{
	this->Pos = pos;
	this->Scale = scale;
	this->RotY = angle;
}


DxObject::~DxObject()
{
}

XMMATRIX DxObject::GetWorld()
{
	XMMATRIX result = XMMatrixScaling(Scale.x, Scale.y, Scale.z) * XMMatrixRotationY(RotY) * XMMatrixTranslationFromVector(Pos.ToXMVector());
	return XMMatrixTranspose(result);
}

void DxObject::Draw()
{
	Model->Draw();
}

void DxObject::Update()
{
	Pos += Velocity * DELTA_TIME;
	RotY += RotYSpeed * DELTA_TIME;
}

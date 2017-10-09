#include "DxCamera.h"



DxCamera::DxCamera(Vector3 Eye, Vector3 At, Vector3 Up, int Width, int Height, float FOV)
{
	this->Eye = Eye;
	this->At = At;
	this->Up = Up;
	this->Width = Width;
	this->Height = Height;
	this->FOV = FOV;
}


DxCamera::~DxCamera()
{
}

XMMATRIX DxCamera::GetViewMatrix()
{
	XMMATRIX result = XMMatrixLookAtLH(Eye.ToXMVector(), At.ToXMVector(), Up.ToXMVector());
	return XMMatrixTranspose(result);
}

XMMATRIX DxCamera::GetProjectionMatrix()
{
	XMMATRIX result = XMMatrixPerspectiveFovLH(FOV, (FLOAT) Width / (FLOAT)Height, NEAR_PLANE, FAR_PLANE);
	return XMMatrixTranspose(result);
}

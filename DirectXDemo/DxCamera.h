#pragma once
#include "main.h"
//this is a camera class
//can calculate view and projection matrices
class DxCamera
{
public:
	DxCamera(Vector3 Eye, Vector3 At, Vector3 Up, int Width, int Height, float FOV = XM_PIDIV4);
	~DxCamera();

	XMMATRIX GetViewMatrix();
	XMMATRIX GetProjectionMatrix();

	Vector3 Eye;		//camera position
	Vector3 At;			//look at position
	int Width;			//viewport width
	int Height;			//viewport height

private:
	
	Vector3 Up;			//up vector
	float FOV;			//field of view in radians
};


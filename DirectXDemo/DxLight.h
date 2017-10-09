#pragma once
#include "DxCamera.h"
//light class
//since it is used as a camera, it inherits from a camera class
class DxLight :
	public DxCamera
{
public:
	DxLight(Vector3 pos, Vector3 At, const Vector3 color);
	~DxLight();
	Vector3 Color;	//light color
};


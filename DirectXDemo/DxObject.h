#pragma once
#include "main.h"
#include "DxModel.h"
#include "DxTexture.h"
#include "DxTime.h"
//this class contains all information needed to draw an object in the scene
class DxObject
{
public:
	DxObject(Vector3 pos, Vector3 scale, float angle=0);
	~DxObject();
	std::shared_ptr<DxModel> Model;	
	Vector3 Pos;			//object position
	Vector3 Scale;			//object scale
	float RotY = 0;			//object y rotation. I should definitely turn this into a full quaternion rotation at some point

	Vector3 Velocity;		//object velocity
	float RotYSpeed = 0;	//rot y angular speed
	//get scale * rotation * translation matrix of this object
	XMMATRIX GetWorld();	
	void Draw();
	//update the pos and rotation of this object
	void Update();			
};


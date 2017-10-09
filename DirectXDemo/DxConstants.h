#pragma once
#include <memory>
//this is a placeholder class for constants
//usually this would be kept in a cofig file
//I just jammed all the random constants here, so that I would not need to look for them everywhere
class DxConstants
{
public:
	DxConstants();
	~DxConstants();
	float Epsilon;
	int LightResolution;
	float NearPlane;
	float FarPlane;
	static std::shared_ptr<DxConstants> Instance();
private:
	static std::shared_ptr<DxConstants> constantsSingleton;
};
#define CONSTANTS DxConstants::Instance()
#define EPSILON CONSTANTS->Epsilon
#define LIGHT_RESOLUTION CONSTANTS->LightResolution
#define NEAR_PLANE CONSTANTS->NearPlane
#define FAR_PLANE CONSTANTS->FarPlane


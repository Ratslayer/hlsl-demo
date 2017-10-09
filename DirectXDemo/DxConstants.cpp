#include "DxConstants.h"

std::shared_ptr<DxConstants> DxConstants::constantsSingleton = std::shared_ptr<DxConstants>(new DxConstants());

DxConstants::DxConstants()
{
	Epsilon = 0.0001f;
	LightResolution = 2048;
	NearPlane = 1;
	FarPlane = 50;
}


DxConstants::~DxConstants()
{
}

std::shared_ptr<DxConstants> DxConstants::Instance()
{
	return constantsSingleton;
}

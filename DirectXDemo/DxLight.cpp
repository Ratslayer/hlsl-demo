#include "DxLight.h"



DxLight::DxLight(Vector3 pos, Vector3 At, Vector3 color)
	: DxCamera(pos, At, Vector3::AreParallel(Eye-At, Vector3(0, 1, 0)) ? Vector3(0, 1, 0) : Vector3(0, 0, 1), LIGHT_RESOLUTION, LIGHT_RESOLUTION, XM_PIDIV2)
{
	Color=color;
}


DxLight::~DxLight()
{
}
#include "DxTime.h"
std::shared_ptr<DxTime> DxTime::timeSingleton = std::shared_ptr<DxTime>(new DxTime());


DxTime::DxTime()
{
}


DxTime::~DxTime()
{
}

void DxTime::Update()
{
	if (DxDevice::Instance()->DriverType == D3D_DRIVER_TYPE_REFERENCE)
	{
		deltaTime += (float)XM_PI * 0.0125f;
	}
	else
	{
		ULONGLONG timeCur = GetTickCount64();
		if (startTime == 0)
		{
			startTime = timeCur;
			lastTime = (timeCur - startTime) / 1000.0f;
		}
		float newLastTime = (timeCur - startTime) / 1000.0f;
		deltaTime = newLastTime - lastTime;
		lastTime = newLastTime;
	}
}

std::shared_ptr<DxTime> DxTime::Instance()
{
	return timeSingleton;
}

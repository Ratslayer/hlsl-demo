#pragma once
#include "main.h"
//This is a time keeping singleton class
//It provides the system with a Unity-style Time object that allows you to access time elapsed between frames
class DxTime
{
public:
	DxTime();
	~DxTime();

	float deltaTime = 0.0f;
	ULONGLONG startTime = 0;
	ULONGLONG totalTime = 0;
	void Update();
	static std::shared_ptr<DxTime> Instance();
private:
	float lastTime = 0.0f;
	static std::shared_ptr<DxTime> timeSingleton;
};
#define TIME DxTime::Instance()
#define DELTA_TIME TIME->deltaTime

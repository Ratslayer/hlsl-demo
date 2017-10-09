#pragma once
#include "DxScene.h"
//this is the factory for the scene
class DxSceneFactory
{
public:
	DxSceneFactory();
	~DxSceneFactory();
	static std::shared_ptr<DxScene> GetDefaultScene();
};


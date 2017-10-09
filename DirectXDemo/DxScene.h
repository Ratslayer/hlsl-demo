#pragma once
#include "main.h"
#include "DxCamera.h"
#include "DxObject.h"
#include "DxLight.h"
//this class contains all objects in the scene
//it's a singleton class for the demo's purpose, but should probably not be
class DxScene
{
public:
	DxScene();
	~DxScene();
	std::shared_ptr<DxCamera> MainCamera;
	std::vector<std::shared_ptr<DxObject>> Objects;
	std::vector<std::shared_ptr<DxLight>> Lights;

	void Update();
	static void Initialize();
	static std::shared_ptr<DxScene> Instance();
private:
	static std::shared_ptr<DxScene> sceneSingleton;
};
#define SCENE DxScene::Instance()


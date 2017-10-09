#include "DxScene.h"
#include "DxSceneFactory.h"
std::shared_ptr<DxScene> DxScene::sceneSingleton = nullptr;

DxScene::DxScene()
{
}


DxScene::~DxScene()
{
}

void DxScene::Update()
{
	for (int i = 0; i < Objects.size(); i++)
	{
		Objects[i]->Update();
	}
}

void DxScene::Initialize()
{
	sceneSingleton = DxSceneFactory::GetDefaultScene();
}

std::shared_ptr<DxScene> DxScene::Instance()
{
	return sceneSingleton;
}

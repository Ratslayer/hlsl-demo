#include "DxInputManager.h"



DxInputManager::DxInputManager()
{
}


DxInputManager::~DxInputManager()
{
}

void DxInputManager::ProcessKey(WPARAM key)
{
	float speed = 25;
	Vector3 upVelocity = Vector3(0, 1, 0) * speed;
	Vector3 rightVelocity = Vector3(1, 0, 0) * speed;
	switch (key)
	{
	case 0x31:
		RENDERER->SetAsFinalTarget(RENDERER->CombinedTarget);
		break;
	case 0x32:
		RENDERER->SetAsFinalTarget(RENDERER->DiffuseTarget);
		break;
	case 0x33:
		RENDERER->SetAsFinalTarget(RENDERER->NormalTarget);
		break;
	case 0x34:
		RENDERER->SetAsFinalTarget(RENDERER->WorldTarget);
		break;
	case 0x35:
		RENDERER->SetAsFinalTarget(RENDERER->LightDepthTarget);
		break;
	case 0x36:
		RENDERER->SetAsFinalTarget(RENDERER->DebugLightTarget);
		break;
	case 0x37:
		RENDERER->SetAsFinalTarget(RENDERER->DebugSpecularTarget);
		break;
	case VK_LEFT:
		SCENE->MainCamera->Eye -= rightVelocity * DELTA_TIME;
		break;
	case VK_RIGHT:
		SCENE->MainCamera->Eye += rightVelocity * DELTA_TIME;
		break;
	case VK_UP:
		SCENE->MainCamera->Eye += upVelocity * DELTA_TIME;
		break;
	case VK_DOWN:
		SCENE->MainCamera->Eye -= upVelocity * DELTA_TIME;
		break;
	case VK_ESCAPE:
		PostQuitMessage(0);
		break;
	}
}

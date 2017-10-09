#include "DxSceneFactory.h"



DxSceneFactory::DxSceneFactory()
{
}


DxSceneFactory::~DxSceneFactory()
{
}

std::shared_ptr<DxScene> DxSceneFactory::GetDefaultScene()
{
	std::shared_ptr<DxMaterial> seafloor = std::shared_ptr<DxMaterial>(new DxMaterial(L"seafloor.dds", L"seafloor.dds"));
	std::shared_ptr<DxMaterial> rocks = std::shared_ptr<DxMaterial>(new DxMaterial(L"rocks_diffuse.dds", L"rocks_normal.dds"));
	std::shared_ptr<DxScene> result(new DxScene());
	result->MainCamera = std::shared_ptr<DxCamera>(new DxCamera(Vector3(10, 15, -25.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0, 1, 0), DEVICE_MANAGER->Width, DEVICE_MANAGER->Height));
	

	std::shared_ptr<DxObject> object = std::shared_ptr<DxObject>(new DxObject(Vector3(0, 0, 0), Vector3(20, 0.1f, 20)));
	object->Model = std::shared_ptr<DxModel>(new DxModel(rocks));
	result->Objects.push_back(object);

	
	object = std::shared_ptr<DxObject>(new DxObject(Vector3(0, 2, 0), Vector3(1, 2, 1)));
	object->Model = std::shared_ptr<DxModel>(new DxModel(rocks));
	object->RotY = XM_PIDIV4;
	result->Objects.push_back(object);

	object = std::shared_ptr<DxObject>(new DxObject(Vector3(-10, 6, 0), Vector3(3, 6, 3)));
	object->Model = std::shared_ptr<DxModel>(new DxModel(rocks));
	object->RotY = XM_PIDIV4;
	result->Objects.push_back(object);

	std::shared_ptr<DxLight> light = std::shared_ptr<DxLight>(new DxLight(Vector3(10, 8, 0), Vector3(0, 0, 0), Vector3(3, 3, 3)));
	result->Lights.push_back(light);
	return result;
}

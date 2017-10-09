#pragma once
#include "main.h"
//This is the class that contains most device data
//Code is mostly taken from MS tutorials
class DxDevice
{
public:
	~DxDevice();

	static std::shared_ptr<DxDevice> Instance();
	//create device, context and chain
	static HRESULT InitDevice(HWND hwnd);

	D3D_DRIVER_TYPE                     DriverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL                   FeatureLevel = D3D_FEATURE_LEVEL_11_0;

	ComPtr<ID3D11Device>                       Device = nullptr;
	ComPtr<ID3D11DeviceContext>                Context = nullptr;
	ComPtr<IDXGISwapChain>                     SwapChain = nullptr;

	ComPtr<ID3D11Texture2D> GetBackBuffer();
	int Width;
	int Height;

private:
	static std::shared_ptr<DxDevice> deviceSingleton;
	DxDevice();
	
	//this is data that is used in case DX 11.1 is enabled
	ComPtr<ID3D11Device1>                      Device1 = nullptr;
	ComPtr<ID3D11DeviceContext1>               Context1 = nullptr;
	ComPtr<IDXGISwapChain1>                    SwapChain1 = nullptr;
	
};
#define DEVICE_MANAGER DxDevice::Instance()
#define DEVICE DEVICE_MANAGER->Device
#define SWAP_CHAIN DEVICE_MANAGER->SwapChain
#define CONTEXT DEVICE_MANAGER->Context


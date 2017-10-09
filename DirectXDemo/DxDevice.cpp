#include "DxDevice.h"
std::shared_ptr<DxDevice> DxDevice::deviceSingleton = nullptr;
ComPtr<ID3D11Texture2D> DxDevice::GetBackBuffer()
{
	ID3D11Texture2D* result;
	HRESULT hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&result));
	ASSERT_HR(hr, "Could not fetch swap chain back buffer.");
	return ComPtr<ID3D11Texture2D>(result);
}
DxDevice::DxDevice()
{
}
DxDevice::~DxDevice()
{
}
std::shared_ptr<DxDevice> DxDevice::Instance()
{
	return deviceSingleton;
}
HRESULT DxDevice::InitDevice(HWND hwnd)
{
	HRESULT hr = S_OK;
	deviceSingleton = std::shared_ptr<DxDevice>(new DxDevice());
	RECT rc;
	GetClientRect(hwnd, &rc);
	deviceSingleton->Width = rc.right - rc.left;
	deviceSingleton->Height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		deviceSingleton->DriverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDevice(nullptr, deviceSingleton->DriverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &deviceSingleton->Device, &deviceSingleton->FeatureLevel, &deviceSingleton->Context);

		if (hr == E_INVALIDARG)
		{
			// DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
			hr = D3D11CreateDevice(nullptr, deviceSingleton->DriverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
				D3D11_SDK_VERSION, &deviceSingleton->Device, &deviceSingleton->FeatureLevel, &deviceSingleton->Context);
		}

		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
		return hr;

	// Obtain DXGI factory from device (since we used nullptr for pAdapter above)
	IDXGIFactory1* dxgiFactory = nullptr;
	{
		IDXGIDevice* dxgiDevice = nullptr;
		hr = deviceSingleton->Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
		if (SUCCEEDED(hr))
		{
			IDXGIAdapter* adapter = nullptr;
			hr = dxgiDevice->GetAdapter(&adapter);
			if (SUCCEEDED(hr))
			{
				hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
				adapter->Release();
			}
			dxgiDevice->Release();
		}
	}
	if (FAILED(hr))
		return hr;

	// Create swap chain
	IDXGIFactory2* dxgiFactory2 = nullptr;
	hr = dxgiFactory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2));
	if (dxgiFactory2)
	{
		// DirectX 11.1 or later
		hr = deviceSingleton->Device->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(deviceSingleton->Device1.GetAddressOf()));
		if (SUCCEEDED(hr))
		{
			(void)deviceSingleton->Context->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(deviceSingleton->Context1.GetAddressOf()));
		}

		DXGI_SWAP_CHAIN_DESC1 sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.Width = deviceSingleton->Width;
		sd.Height = deviceSingleton->Height;
		sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;

		hr = dxgiFactory2->CreateSwapChainForHwnd(deviceSingleton->Device.Get(), hwnd, &sd, nullptr, nullptr, &deviceSingleton->SwapChain1);
		if (SUCCEEDED(hr))
		{
			IDXGISwapChain* tempChain;
			hr = deviceSingleton->SwapChain1->QueryInterface(__uuidof(IDXGISwapChain), reinterpret_cast<void**>(&tempChain));
			deviceSingleton->SwapChain = ComPtr<IDXGISwapChain>(tempChain);
		}
		ASSERT_HR(hr, "Could not create a swap chain.");
		dxgiFactory2->Release();
	}
	else
	{
		// DirectX 11.0 systems
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 1;
		sd.BufferDesc.Width = deviceSingleton->Width;
		sd.BufferDesc.Height = deviceSingleton->Height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = hwnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;

		hr = dxgiFactory->CreateSwapChain(deviceSingleton->Device.Get(), &sd, &deviceSingleton->SwapChain);
		ASSERT_HR(hr, "Could not create a swap chain.");
	}

	// Note this tutorial doesn't handle full-screen swapchains so we block the ALT+ENTER shortcut
	dxgiFactory->MakeWindowAssociation(hwnd, DXGI_MWA_NO_ALT_ENTER);

	dxgiFactory->Release();
	return hr;
}
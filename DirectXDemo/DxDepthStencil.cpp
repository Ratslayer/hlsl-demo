#include "DxDepthStencil.h"



DxDepthStencil::DxDepthStencil(UINT Width, UINT Height)
	: DxTexture(Width, Height, DXGI_FORMAT_R24G8_TYPELESS, DXGI_FORMAT_R24_UNORM_X8_TYPELESS, D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE, D3D11_USAGE_DEFAULT)
{
	D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc;
	dsv_desc.Flags = 0;
	dsv_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsv_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsv_desc.Texture2D.MipSlice = 0;

	DEVICE->CreateDepthStencilView(Texture.Get(), &dsv_desc, &DepthStencilView);
}


DxDepthStencil::~DxDepthStencil()
{
}

void DxDepthStencil::Clear()
{
	DxDevice::Instance()->Context->ClearDepthStencilView(DepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

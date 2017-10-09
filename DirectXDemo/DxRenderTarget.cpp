#include "DxRenderTarget.h"



DxRenderTarget::DxRenderTarget(ComPtr<ID3D11Texture2D> texture, bool createView)
	:DxTexture(texture, createView)
{
	HRESULT hr = DEVICE->CreateRenderTargetView(texture.Get(), nullptr, &RenderTargetView);
	ASSERT_HR(hr, "Could not create render target view from supplied texture.");
}

DxRenderTarget::DxRenderTarget(int width, int height, DXGI_FORMAT format)
	: DxTexture(width, height, format, format, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE, D3D11_USAGE_DEFAULT)
{
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	rtvDesc.Format = format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0;
	HRESULT hr = DEVICE->CreateRenderTargetView(Texture.Get(), &rtvDesc, &RenderTargetView);
	ASSERT_HR(hr, "Could not create render target view for supplied format.");
	this->Width = width;
	this->Height = height;
}


DxRenderTarget::~DxRenderTarget()
{
}

ComPtr<ID3D11RenderTargetView> DxRenderTarget::GetRenderTarget()
{
	return RenderTargetView;
}

void DxRenderTarget::Clear(const XMVECTORF32 &color)
{
	CONTEXT->ClearRenderTargetView(RenderTargetView.Get(), color);
}

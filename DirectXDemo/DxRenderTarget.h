#pragma once
#include "DxTexture.h"
//this is a render target wrapper class that describes a rendertaget that can be used as a texture
class DxRenderTarget :
	public DxTexture
{
public:
	DxRenderTarget(ComPtr<ID3D11Texture2D> texture, bool createView);
	DxRenderTarget(int Width, int Height, DXGI_FORMAT format);
	~DxRenderTarget();

	ComPtr<ID3D11RenderTargetView> GetRenderTarget();
	//clear all pixels in the target to a specified color
	void Clear(const XMVECTORF32 &color = Colors::Black);
	int Width;
	int Height;
private:
	ComPtr<ID3D11RenderTargetView> RenderTargetView;
};


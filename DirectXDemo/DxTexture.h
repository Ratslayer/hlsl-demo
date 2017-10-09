#pragma once
#include "main.h"
//this is the base 2D Texture class that can be a texture loaded from file, or a RenderTarget
class DxTexture
{
public:
	DxTexture(std::wstring fileName);
	DxTexture(ComPtr<ID3D11Texture2D> texture, bool createView=true);
	DxTexture(UINT Width, UINT Height, DXGI_FORMAT format, DXGI_FORMAT viewFormat, UINT bindFlags, D3D11_USAGE usage);
	~DxTexture();

	ComPtr<ID3D11Texture2D> Texture;
	ComPtr<ID3D11ShaderResourceView> TextureView;
	//bind texture to a specific shader resource texture slot
	void AttachToPSSlot(int slot);
	//unbind texture form the slot
	void Unattach();
private:
	void CreateShaderResourceView(DXGI_FORMAT format);
	int _slot;
};


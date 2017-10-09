#include "DxTexture.h"



DxTexture::DxTexture(std::wstring fileName)
{
	// Load the Texture
	ID3D11Resource* texture = nullptr;
	HRESULT hr = CreateDDSTextureFromFile(DxDevice::Instance()->Device.Get(), fileName.c_str(), &texture, &TextureView);
	ASSERT_HR(hr, L"Could not create texture from " + fileName + L". Maybe the file is missing. Maybe something else.");
	hr = texture->QueryInterface(__uuidof(ID3D11Texture2D), (void**)&Texture);
	ASSERT_HR(hr, L"Could not query texture from texture view for " + fileName);
}
DxTexture::DxTexture(ComPtr<ID3D11Texture2D> texture, bool createView)
{
	Texture = texture;
	if (createView)
	{
		CreateShaderResourceView(DXGI_FORMAT_R24_UNORM_X8_TYPELESS);
	}
}
DxTexture::DxTexture(UINT Width, UINT Height, DXGI_FORMAT format, DXGI_FORMAT viewFormat, UINT bindFlags, D3D11_USAGE usage)
{
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = Width;
	descDepth.Height = Height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = format;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = usage;
	descDepth.BindFlags = bindFlags;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	HRESULT hr = DEVICE->CreateTexture2D(&descDepth, nullptr, &Texture);
	ASSERT_HR(hr, "Could not create texture.");

	CreateShaderResourceView(viewFormat);
}
DxTexture::~DxTexture()
{
}

void DxTexture::AttachToPSSlot(int slot)
{
	_slot = slot;
	CONTEXT->PSSetShaderResources(slot, 1, TextureView.GetAddressOf());
}

void DxTexture::Unattach()
{
	ID3D11ShaderResourceView* nullSRV[1] = { nullptr };
	CONTEXT->PSSetShaderResources(_slot, 1, nullSRV);
}

void DxTexture::CreateShaderResourceView(DXGI_FORMAT format)
{
	D3D11_SHADER_RESOURCE_VIEW_DESC sr_desc;
	sr_desc.Format = format;
	sr_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	sr_desc.Texture2D.MostDetailedMip = 0;
	sr_desc.Texture2D.MipLevels = -1;

	HRESULT hr = DEVICE->CreateShaderResourceView(Texture.Get(), &sr_desc, &TextureView);
	ASSERT_HR(hr, "Could not create texture view.");
}

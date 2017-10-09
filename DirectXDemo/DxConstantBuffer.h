#pragma once
#include "main.h"
//this is a template class that can describe any constant buffer and structure pair
//it is used to pass data to shaders
template<typename BufferStruct> class DxConstantBuffer
{
public:
	DxConstantBuffer()
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(BufferStruct);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		HRESULT hr = DEVICE->CreateBuffer(&bd, nullptr, &_buffer);
		ASSERT_HR(hr, "Could not create a constant buffer.");
	}
	~DxConstantBuffer() 
	{
	}
	//copy buffer data from CPU to GPU
	void UpdateBuffer(const BufferStruct &bufferData)
	{
		CONTEXT->UpdateSubresource(_buffer.Get(), 0, nullptr, &bufferData, 0, 0);
	}
	void SetAsVSBuffer(UINT slot)
	{
		CONTEXT->VSSetConstantBuffers(slot, 1, _buffer.GetAddressOf());
	}
	void SetAsPSBuffer(UINT slot)
	{
		CONTEXT->PSSetConstantBuffers(slot, 1, _buffer.GetAddressOf());
	}
private:
	ComPtr<ID3D11Buffer> _buffer;
	
};


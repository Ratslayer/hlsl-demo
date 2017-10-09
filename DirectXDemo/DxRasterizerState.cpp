#include "DxRasterizerState.h"



DxRasterizerState::DxRasterizerState()
{

	D3D11_RASTERIZER_DESC rasterizerState;
	rasterizerState.FillMode = D3D11_FILL_SOLID;
	rasterizerState.CullMode = D3D11_CULL_FRONT;
	rasterizerState.FrontCounterClockwise = true;
	rasterizerState.DepthBias = false;
	rasterizerState.DepthBiasClamp = 0;
	rasterizerState.SlopeScaledDepthBias = 0;
	rasterizerState.DepthClipEnable = true;
	rasterizerState.ScissorEnable = true;
	rasterizerState.MultisampleEnable = false;
	rasterizerState.AntialiasedLineEnable = false;
	DEVICE->CreateRasterizerState(&rasterizerState, &_state);
}

DxRasterizerState::DxRasterizerState(D3D11_RASTERIZER_DESC desc)
{
	DEVICE->CreateRasterizerState(&desc, &_state);
}


DxRasterizerState::~DxRasterizerState()
{
}

void DxRasterizerState::Set()
{
	CONTEXT->RSSetState(_state.Get());
}

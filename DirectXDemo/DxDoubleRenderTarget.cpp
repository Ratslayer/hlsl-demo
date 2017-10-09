#include "DxDoubleRenderTarget.h"



DxDoubleRenderTarget::DxDoubleRenderTarget(int Width, int Height, DXGI_FORMAT format)
{
	TargetTarget = std::shared_ptr<DxRenderTarget>(new DxRenderTarget(Width, Height, format));
	TextureTarget = std::shared_ptr<DxRenderTarget>(new DxRenderTarget(Width, Height, format));
}


DxDoubleRenderTarget::~DxDoubleRenderTarget()
{
}

std::shared_ptr<DxRenderTarget> DxDoubleRenderTarget::GetTarget()
{
	return TargetTarget;
}

std::shared_ptr<DxTexture> DxDoubleRenderTarget::GetTexture()
{
	return TextureTarget;
}

void DxDoubleRenderTarget::Swap()
{
	std::shared_ptr<DxRenderTarget> temp = TargetTarget;
	TargetTarget = TextureTarget;
	TextureTarget = temp;
}

void DxDoubleRenderTarget::Clear()
{
	TargetTarget->Clear();
	TextureTarget->Clear();
}

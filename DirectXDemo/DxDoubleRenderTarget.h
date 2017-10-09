#pragma once
#include "DxRenderTarget.h"
//This is a render target that can be read from and rendered to at the same time
//It achieves this by having 2 rendertargets and swapping between them whenever you need to bind one or the other
class DxDoubleRenderTarget
{
public:
	DxDoubleRenderTarget(int Width, int Height, DXGI_FORMAT format);
	~DxDoubleRenderTarget();
	//get the target that is used as a target
	std::shared_ptr<DxRenderTarget> GetTarget();
	//get target that is used as a texture
	std::shared_ptr<DxTexture> GetTexture();
	//swap target and texture places
	void Swap();
	//clear both target and texture
	void Clear();

private:
	std::shared_ptr<DxRenderTarget> TargetTarget;
	std::shared_ptr<DxRenderTarget> TextureTarget;
};


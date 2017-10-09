#include "DxRenderTargetCollection.h"



DxRenderTargetCollection::DxRenderTargetCollection()
{
}


DxRenderTargetCollection::~DxRenderTargetCollection()
{
}

void DxRenderTargetCollection::AddTarget(std::shared_ptr<DxRenderTarget> target)
{
	_targets.push_back(target);
}

void DxRenderTargetCollection::AddDepth(std::shared_ptr<DxDepthStencil> depth)
{
	_depth = depth;
}

void DxRenderTargetCollection::Clear(const XMVECTORF32 &color)
{
	for (int i = 0; i < _targets.size(); i++)
	{
		_targets[i]->Clear(color);
	}
	if (_depth)
	{
		_depth->Clear();
	}
}

void DxRenderTargetCollection::Bind()
{
	_views.clear();
	for (int i = 0; i < _targets.size(); i++)
	{
		_views.push_back(_targets[i]->GetRenderTarget().Get());
	}
	ID3D11DepthStencilView* depth = _depth ? _depth->DepthStencilView.Get() : nullptr;
	BindViews(depth);
}

void DxRenderTargetCollection::Unbind()
{
	_views.clear();
	for (int i = 0; i < _targets.size(); i++)
	{
		_views.push_back(nullptr);
	}

	BindViews(nullptr);
}

UINT DxRenderTargetCollection::GetWidth()
{
	return _targets[0]->Width;
}

UINT DxRenderTargetCollection::GetHeight()
{
	return _targets[0]->Height;
}

void DxRenderTargetCollection::BindViews(ID3D11DepthStencilView *depth)
{
	CONTEXT->OMSetRenderTargets(_views.size(), _views.data(), depth);
}

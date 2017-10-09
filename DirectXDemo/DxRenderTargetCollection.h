#pragma once
#include "main.h"
#include "DxRenderTarget.h"
#include "DxDepthStencil.h"
//This is a target collection that simplifies binding multiple targets as outputs
class DxRenderTargetCollection
{
public:
	DxRenderTargetCollection();
	~DxRenderTargetCollection();
	//add target to the list of targets
	void AddTarget(std::shared_ptr<DxRenderTarget> target);
	//set depth target. If 1 exists already, replace it
	void AddDepth(std::shared_ptr<DxDepthStencil> depth);
	//clear all targets and depth, if it exists
	void Clear(const XMVECTORF32 &color = Colors::Black);
	//bind all targets
	void Bind();
	//unbind all targets
	void Unbind();
	//all targets are of same resolution
	UINT GetWidth();
	UINT GetHeight();
private:
	std::vector<std::shared_ptr<DxRenderTarget>>	_targets;
	std::shared_ptr<DxDepthStencil>					_depth;
	std::vector<ID3D11RenderTargetView*>			_views;

	void BindViews(ID3D11DepthStencilView *depth);
};


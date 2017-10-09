#include "DxRenderer.h"

std::shared_ptr<DxRenderer> DxRenderer::rendererSingleton = nullptr;
void DxRenderer::SetAsFinalTarget(std::shared_ptr<DxTexture> target)
{
	FinalTarget = target;
}
DxRenderer::DxRenderer()
{
	LoadDefaults(DxDevice::Instance()->Width, DxDevice::Instance()->Height);
}
DxRenderer::~DxRenderer()
{
}
void DxRenderer::Render()
{
	BackBufferTarget->Clear();
	//Scene Pass
	DxRenderTargetCollection targets;
	targets.AddTarget(WorldTarget);
	targets.AddTarget(DiffuseTarget);
	targets.AddTarget(NormalTarget);
	targets.AddDepth(SceneDepth);
	targets.Clear();
	DrawScene(nullptr, SceneEffect, targets);
	//Light pass for every light in the scene
	LightTarget->Clear();
	SpecularTarget->Clear();
	for (int i = 0; i < SCENE->Lights.size(); i++)
	{
		std::shared_ptr<DxLight> light = SCENE->Lights[i];
		//shadow pass
		//use a special shadow rasterizer to reduce shadow artefacts
		ShadowRasterizer->Set();
		targets = DxRenderTargetCollection();
		targets.AddTarget(LightDepthTarget);
		targets.AddDepth(LightDepth);
		targets.Clear(Colors::White);
		//draw scene from light's point of view
		DrawScene(light, DepthEffect, targets);
		DefaultRasterizer->Set();

		//lighting pass
		targets = DxRenderTargetCollection();
		targets.AddTarget(LightTarget->GetTarget());
		targets.AddTarget(SpecularTarget->GetTarget());
		targets.Bind();
		
		LightTarget->GetTexture()->AttachToPSSlot(0);
		SpecularTarget->GetTexture()->AttachToPSSlot(1);
		WorldTarget->AttachToPSSlot(2);
		NormalTarget->AttachToPSSlot(3);
		LightDepthTarget->AttachToPSSlot(4);
		ClampSampler->Bind();
		UpdateLightBuffer(SCENE->MainCamera, light);
		DrawFullscreen(LightingEffect, targets);

		LightTarget->Swap();
		SpecularTarget->Swap();
	}
	//combination pass
	LightTarget->GetTexture()->AttachToPSSlot(0);
	SpecularTarget->GetTexture()->AttachToPSSlot(1);
	DiffuseTarget->AttachToPSSlot(2);
	ClampSampler->Bind();

	targets = DxRenderTargetCollection();
	targets.AddTarget(CombinedTarget);
	DrawFullscreen(LightingCombinationEffect, targets);

	//for debugging purposes
	CopyTextureToTarget(LightTarget->GetTexture(), DebugLightTarget);
	CopyTextureToTarget(SpecularTarget->GetTexture(), DebugSpecularTarget);
	//final texture presentation
	CopyTextureToTarget(FinalTarget, nullptr);
	SWAP_CHAIN->Present(0, 0);
}

void DxRenderer::DrawScene(std::shared_ptr<DxCamera> camera, std::shared_ptr<DxEffect> effect, DxRenderTargetCollection &targets)
{
	targets.Bind();
	effect->Apply();
	//default to main camera if none are given
	if (!camera)
	{
		camera = SCENE->MainCamera;
	}
	WrapSampler->Bind();
	UpdateCameraBuffer(camera);
	SetViewport(camera->Width, camera->Height);
	//draw every object in the scene
	for (int i = 0; i < SCENE->Objects.size(); i++)
	{
		std::shared_ptr<DxObject> object = SCENE->Objects[i];
		UpdateObjectBuffer(object);
		object->Draw();
	}
	targets.Unbind();
}

void DxRenderer::LoadDefaults(UINT Width, UINT Height)
{
	//render targets
	BackBufferTarget = std::shared_ptr<DxRenderTarget>(new DxRenderTarget(DEVICE_MANAGER->GetBackBuffer(), false));
	DiffuseTarget = std::shared_ptr<DxRenderTarget>(new DxRenderTarget(Width, Height, DXGI_FORMAT_R16G16B16A16_FLOAT));
	NormalTarget = std::shared_ptr<DxRenderTarget>(new DxRenderTarget(Width, Height, DXGI_FORMAT_R16G16B16A16_FLOAT));
	WorldTarget = std::shared_ptr<DxRenderTarget>(new DxRenderTarget(Width, Height, DXGI_FORMAT_R16G16B16A16_FLOAT));
	LightTarget = std::shared_ptr<DxDoubleRenderTarget>(new DxDoubleRenderTarget(Width, Height, DXGI_FORMAT_R16G16B16A16_FLOAT));
	SpecularTarget = std::shared_ptr<DxDoubleRenderTarget>(new DxDoubleRenderTarget(Width, Height, DXGI_FORMAT_R16G16B16A16_FLOAT));
	DebugLightTarget = std::shared_ptr<DxRenderTarget>(new DxRenderTarget(Width, Height, DXGI_FORMAT_R16G16B16A16_FLOAT));
	DebugSpecularTarget = std::shared_ptr<DxRenderTarget>(new DxRenderTarget(Width, Height, DXGI_FORMAT_R16G16B16A16_FLOAT));
	CombinedTarget = std::shared_ptr<DxRenderTarget>(new DxRenderTarget(Width, Height, DXGI_FORMAT_R16G16B16A16_FLOAT));
	LightDepthTarget = std::shared_ptr<DxRenderTarget>(new DxRenderTarget(LIGHT_RESOLUTION, LIGHT_RESOLUTION, DXGI_FORMAT_R32_FLOAT));
	SetAsFinalTarget(CombinedTarget);
	//depth stencils
	SceneDepth = std::shared_ptr<DxDepthStencil>(new DxDepthStencil(Width, Height));
	LightDepth = std::shared_ptr<DxDepthStencil>(new DxDepthStencil(LIGHT_RESOLUTION, LIGHT_RESOLUTION));
	//buffers
	CameraBuffer= std::shared_ptr<DxConstantBuffer<CBCamera>>(new DxConstantBuffer<CBCamera>());
	ModelBuffer = std::shared_ptr<DxConstantBuffer<CBModel>>(new DxConstantBuffer<CBModel>());
	LightBuffer = std::shared_ptr<DxConstantBuffer<CBLight>>(new DxConstantBuffer<CBLight>());

	//CONTEXT->OMSetRenderTargets(1, BackBufferTarget->GetRenderTarget().GetAddressOf(), SceneDepth->DepthStencilView.Get());
	// Setup the viewport
	SetViewport(Width, Height);

	//samplers
	WrapSampler = std::shared_ptr<DxSamplerState>(new DxSamplerState(D3D11_TEXTURE_ADDRESS_WRAP));
	ClampSampler = std::shared_ptr<DxSamplerState>(new DxSamplerState(D3D11_TEXTURE_ADDRESS_CLAMP));
	//rasterizers
	DefaultRasterizer = std::shared_ptr<DxRasterizerState>(new DxRasterizerState());
	D3D11_RASTERIZER_DESC rastDesc;
	rastDesc.FillMode = D3D11_FILL_SOLID;
	rastDesc.CullMode = D3D11_CULL_NONE;
	rastDesc.FrontCounterClockwise = true;
	rastDesc.DepthBias = true;
	rastDesc.DepthBiasClamp = 0.01f;
	rastDesc.SlopeScaledDepthBias = 5;
	rastDesc.DepthClipEnable = true;
	rastDesc.ScissorEnable = true;
	rastDesc.MultisampleEnable = false;
	rastDesc.AntialiasedLineEnable = false;
	ShadowRasterizer = std::shared_ptr<DxRasterizerState>(new DxRasterizerState(rastDesc));
	DefaultRasterizer->Set();
	//effects
	SceneEffect = std::shared_ptr<DxEffect>(new DxEffect(L"SceneEffect.fx", L"SceneEffect.fx"));
	TargetEffect = std::shared_ptr<DxEffect>(new DxEffect(L"2DDrawEffect.fx", L"2DDrawEffect.fx"));
	DepthEffect = std::shared_ptr<DxEffect>(new DxEffect(L"DrawDepth.fx", L"DrawDepth.fx"));
	LightingEffect = std::shared_ptr<DxEffect>(new DxEffect(L"LightEffect.fx", L"LightEffect.fx"));
	LightingCombinationEffect = std::shared_ptr<DxEffect>(new DxEffect(L"LightingMergeEffect.fx", L"LightingMergeEffect.fx"));
}

std::shared_ptr<DxRenderer> DxRenderer::Instance()
{
	return rendererSingleton;
}

void DxRenderer::Initialize()
{
	rendererSingleton = std::shared_ptr<DxRenderer>(new DxRenderer());
}

void DxRenderer::SetViewport(UINT Width, UINT Height)
{
	// Setup the viewport
	D3D11_VIEWPORT vp;
	ZeroMemory(&vp, sizeof(D3D11_VIEWPORT));
	vp.Width = (FLOAT)Width;
	vp.Height = (FLOAT)Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	CONTEXT->RSSetViewports(1, &vp);
}

void DxRenderer::UpdateCameraBuffer(std::shared_ptr<DxCamera> camera)
{
	CBCamera cbCamera;
	cbCamera.mView = camera->GetViewMatrix();
	cbCamera.mProjection = camera->GetProjectionMatrix();
	cbCamera.vEyePos = camera->Eye.ToXMFloat3();
	cbCamera.fFarPlane = FAR_PLANE;

	CameraBuffer->UpdateBuffer(cbCamera);
	CameraBuffer->SetAsVSBuffer(0);
	CameraBuffer->SetAsPSBuffer(0);
}

void DxRenderer::UpdateObjectBuffer(std::shared_ptr<DxObject> object)
{
	CBModel cbModel;
	cbModel.mWorld = object->GetWorld();
	ModelBuffer->UpdateBuffer(cbModel);
	ModelBuffer->SetAsVSBuffer(1);
}

void DxRenderer::UpdateLightBuffer(std::shared_ptr<DxCamera> camera, std::shared_ptr<DxLight> light)
{
	CBLight cbLight;
	cbLight.LightView = light->GetViewMatrix();
	cbLight.LightProj = light->GetProjectionMatrix();
	cbLight.EyePos = camera->Eye.ToXMFloat4();
	cbLight.LightPos = light->Eye.ToXMFloat4();
	cbLight.LightColor = light->Color.ToXMFloat4();
	cbLight.FarPlane = FAR_PLANE;
	cbLight.Bias = 0.0001f;
	cbLight.LightResolution = XMFLOAT2(LIGHT_RESOLUTION, LIGHT_RESOLUTION);
	
	LightBuffer->UpdateBuffer(cbLight);
	LightBuffer->SetAsVSBuffer(0);
	LightBuffer->SetAsPSBuffer(0);
}

void DxRenderer::CopyTextureToTarget(std::shared_ptr<DxTexture> texture, std::shared_ptr<DxRenderTarget> target)
{
	TargetEffect->Apply();
	texture->AttachToPSSlot(0);
	ClampSampler->Bind();
	if (target)
	{
		SetViewport(target->Width, target->Height);
		DxRenderTargetCollection targets;
		targets.AddTarget(target);
		targets.Bind();
		DrawFullscreenQuad();
		targets.Unbind();
	}
	//if target is null, use backbuffer as target
	else
	{
		UseBackBuffer();
		SetViewport(DEVICE_MANAGER->Width, DEVICE_MANAGER->Height);
		DrawFullscreenQuad();
	}
	texture->Unattach();
}
void DxRenderer::DrawFullscreenQuad()
{
	//draw 4 vertices with no data but their indices.
	//Vertex shader will compute their positions from that
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	CONTEXT->Draw(4, 0);
}
void DxRenderer::DrawFullscreen(std::shared_ptr<DxEffect> effect, DxRenderTargetCollection &targets)
{
	SetViewport(targets.GetWidth(), targets.GetHeight());
	effect->Apply();
	targets.Bind();
	DrawFullscreenQuad();
	targets.Unbind();
}

void DxRenderer::UseBackBuffer()
{
	CONTEXT->OMSetRenderTargets(1, BackBufferTarget->GetRenderTarget().GetAddressOf(), nullptr);
}

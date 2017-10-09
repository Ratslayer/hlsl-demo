#pragma once
#include "main.h"
#include "DxCamera.h"
#include "DxScene.h"
#include "DxEffect.h"
#include "DxConstantBuffer.h"
#include "DxDepthStencil.h"
#include "DxRenderTarget.h"
#include "DxSamplerState.h"
#include "DxRasterizerState.h"
#include "DxSceneFactory.h"
#include "DxRenderTargetCollection.h"
#include "DxDoubleRenderTarget.h"
//This is a singleton class that is responsible for drawing the scene
//Since this is a graphics demo, most of the logic is here and this class is extremely bloated.
//TODO: refactor this code into multiple classes to reduce code complexity
class DxRenderer
{
public:
	
	~DxRenderer();
	void Render();
	//Initialization function
	void LoadDefaults(UINT Width, UINT Height);
	//singleton functionality
	static std::shared_ptr<DxRenderer> Instance();
	static void Initialize();
	//Targets that are going to be used in the deferred graphics pipeline
	//Scene pass targets
	std::shared_ptr<DxRenderTarget> DiffuseTarget;			//scene's diffuse color
	std::shared_ptr<DxRenderTarget> NormalTarget;			//scene's normals
	std::shared_ptr<DxRenderTarget> WorldTarget;			//scene's world position
	std::shared_ptr<DxDepthStencil> SceneDepth;				//scene's z-buffer
	//shadow pass targets
	std::shared_ptr<DxRenderTarget> LightDepthTarget;		//light's depth in rendertarget
	std::shared_ptr<DxDepthStencil> LightDepth;				//light's depth in z-buffer
	//light pass targets
	std::shared_ptr<DxDoubleRenderTarget> LightTarget;		//cumulative lighting from all light sources
	std::shared_ptr<DxDoubleRenderTarget> SpecularTarget;	//cumulative specular highlights from all light sources
	//those are transitionary targets that are used to preview double render targets, since they keep swapping
	std::shared_ptr<DxRenderTarget> DebugLightTarget;
	std::shared_ptr<DxRenderTarget> DebugSpecularTarget;
	//combined deferred target
	std::shared_ptr<DxRenderTarget> CombinedTarget;			//combined result: diffuse * lighting + specular
	//draw any target to back buffer, this is mostly used for debugging and demoing purposes
	void SetAsFinalTarget(std::shared_ptr<DxTexture> target);
private:
	DxRenderer();
	static std::shared_ptr<DxRenderer> rendererSingleton;
	//constant buffer structures
	//camera buffer
	struct CBCamera
	{
		XMMATRIX mView;
		XMMATRIX mProjection;
		XMFLOAT3 vEyePos;
		float	 fFarPlane;
	};
	//model buffer
	struct CBModel
	{
		XMMATRIX mWorld;
	};
	//light buffer
	struct CBLight
	{
		XMMATRIX LightView;
		XMMATRIX LightProj;
		XMFLOAT4 EyePos;
		XMFLOAT4 LightPos;
		XMFLOAT4 LightColor;
		float FarPlane;
		float Bias;
		XMFLOAT2 LightResolution;
	};
	//sampler states
	std::shared_ptr<DxSamplerState> WrapSampler;
	std::shared_ptr<DxSamplerState> ClampSampler;
	//rasterizer states
	std::shared_ptr<DxRasterizerState> DefaultRasterizer;
	std::shared_ptr<DxRasterizerState> ShadowRasterizer;
	//effects
	std::shared_ptr<DxEffect> SceneEffect;					//renders the whole scene to multiple targets
	std::shared_ptr<DxEffect> DepthEffect;					//renders the scene's depth. Used for shadow comparisons
	std::shared_ptr<DxEffect> LightingEffect;				//calculates light and specular values based on shadows and normals
	std::shared_ptr<DxEffect> TargetEffect;					//renders a texture to a target, stretchign it if needed
	std::shared_ptr<DxEffect> LightingCombinationEffect;	//combines color, lighting and specular to generate final scene result
	//constant buffer objects
	std::shared_ptr<DxConstantBuffer<CBCamera>> CameraBuffer;
	std::shared_ptr<DxConstantBuffer<CBModel>> ModelBuffer;
	std::shared_ptr<DxConstantBuffer<CBLight>> LightBuffer;

	//render targets
	std::shared_ptr<DxRenderTarget> BackBufferTarget;
	std::shared_ptr<DxTexture> FinalTarget;
	//set viewport to any size
	void SetViewport(UINT Width, UINT Height);
	//helper function that updates camera buffer with data from a camera object
	void UpdateCameraBuffer(std::shared_ptr<DxCamera> camera);
	//helper function that updates model buffer with data from a game object
	void UpdateObjectBuffer(std::shared_ptr<DxObject> object);
	//helper function that updates light buffer with data from a camera and light objects
	void UpdateLightBuffer(std::shared_ptr<DxCamera> camera, std::shared_ptr<DxLight> light);
	//helper function that draws the whole scene from a specific point of view
	//if camera is null, will use scene's main camera
	void DrawScene(std::shared_ptr<DxCamera> camera, std::shared_ptr<DxEffect> effect, DxRenderTargetCollection &targets);
	//draw any texture to any target
	void CopyTextureToTarget(std::shared_ptr<DxTexture> texture, std::shared_ptr<DxRenderTarget> target);
	//apply a post processing effect
	void DrawFullscreen(std::shared_ptr<DxEffect> effect, DxRenderTargetCollection &targets);
	//draw a quad that fits the screen
	//used for 2d effects
	void DrawFullscreenQuad();
	//set back buffer as the render target
	void UseBackBuffer();
};
#define RENDERER DxRenderer::Instance()

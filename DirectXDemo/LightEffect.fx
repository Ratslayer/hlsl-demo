#include "QuadVertexShader.hlsl"
#include "TextureFunctions.h"
//this effect is run for every light in the scene and generates light and specular data
cbuffer LightBuffer : register (b0)
{
	matrix LightView;
	matrix LightProj;
	float4 EyePos;
	float4 LightPos;
	float4 LightColor;
	float FarPlane;
	float Bias;
	float2 LightResolution;
};
SamplerState ClampSampler : register(s0);

Texture2D LightTexture : register(t0);		//last pass lighting data
Texture2D SpecularTexture : register(t1);	//last pass specular data
Texture2D WorldTexture : register(t2);		//world data from scene pass
Texture2D NormalTexture : register(t3);		//normal data from scene pass
Texture2D LightDepthTexture : register(t4);	//shadow data for the light

struct PS_OUTPUT
{
	float4 Light : SV_TARGET0;
	float4 Specular : SV_TARGET1;
};
//pixel shader that outputs to light and specular targets
PS_OUTPUT PS(PS_INPUT input)
{
	PS_OUTPUT output = (PS_OUTPUT)0;
	//get last pass values
	output.Light = LightTexture.Sample(ClampSampler, input.Tex);
	output.Specular = SpecularTexture.Sample(ClampSampler, input.Tex);
	//get light direction
	float4x4 LightViewProj = mul(LightView, LightProj);
	//get position data for the pixel
	float3 world = TexToWorld(WorldTexture.Sample(ClampSampler, input.Tex).xyz, EyePos.xyz, FarPlane);
	//get position from light's point of view
	float4 lightViewPos = mul(float4(world, 1), LightViewProj);
	//get projection texture coordinates for shadow map
	float2 projectTexCoord = VecToTex(float3(lightViewPos.x, lightViewPos.y, 0) / lightViewPos.w).xy;
	projectTexCoord.x = lightViewPos.x / lightViewPos.w / 2.0f + 0.5f;
	projectTexCoord.y = -lightViewPos.y / lightViewPos.w / 2.0f + 0.5f;
	//if texture coordinates are not between 0 and 1, then there is no way this pixel is lit
	if ((saturate(projectTexCoord.x) == projectTexCoord.x) && (saturate(projectTexCoord.y) == projectTexCoord.y))
	{
		//sample adjacent pixels to get Percent Closer Soft Shadows
		float2 pixelOffset = 1 / LightResolution;
		int nExtraSamples = 3;
		float intensity = 0;
		for (int ix = -nExtraSamples; ix < nExtraSamples; ix++)
		{
			for (int iy = -nExtraSamples; iy < nExtraSamples; iy++)
			{
				//get sample depth
				float2 offset = pixelOffset * float2(ix, iy);
				float lightDepth = LightDepthTexture.Sample(ClampSampler, projectTexCoord+offset).r;
				float shadowDepth = lightViewPos.z / lightViewPos.w;
				//if shadowed position is same as lit position, then this pixel is lit
				if (shadowDepth < lightDepth + Bias)
				{
					intensity += 1.0f;
				}
			}
		}
		intensity /= (nExtraSamples * 2 + 1) * (nExtraSamples * 2 + 1);

		float3 normal = normalize(NormalTexture.Sample(ClampSampler, input.Tex).xyz);
		//get normal * light to see how much diffuse light bounces off this pixel
		float lightPart = saturate(dot(normal, saturate(normalize(LightPos.xyz - world))));
		//get normal * eye to see how much specular highlight bounces off this pixel
		float eyePart = saturate(dot(normal, saturate(normalize(EyePos.xyz - world))));
		//calculate diffuse light
		output.Light += float4(saturate(LightColor.xyz * lightPart * intensity), 1);
		//calculate specular light
		//TODO: extract the shiness and specular constants into material
		output.Specular += float4(saturate(LightColor.xyz * 100 * pow(eyePart, 10)) * intensity, 1);
	}
	output.Light.a = 1;
	output.Specular.a = 1;
	return output;
}
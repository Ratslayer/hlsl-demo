#include "QuadVertexShader.hlsl"
//this is the final shader that combines diffuse and lighting to create final result
//the formula is diffuse * light + specular
Texture2D LightTexture : register(t0);
Texture2D SpecularTexture : register(t1);
Texture2D DiffuseTexture : register(t2);

SamplerState ClampSampler : register(s0);

float4 PS(PS_INPUT input) : SV_Target
{
	//fetch texture data
	float3 light = LightTexture.Sample(ClampSampler, input.Tex).rgb;
	float3 specular = SpecularTexture.Sample(ClampSampler, input.Tex).rgb;
	float3 diffuse = DiffuseTexture.Sample(ClampSampler, input.Tex).rgb;
	//compute result
	float4 result = float4(diffuse * light + specular, 1);
	return result;
}

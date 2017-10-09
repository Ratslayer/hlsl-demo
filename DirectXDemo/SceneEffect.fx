#include "VertexInput.h"
#include "TextureFunctions.h"
//This is the effect that is responsible for the first pass in the pipeline
//It takes in objects from a scene and stores their information in multiple render targets
//textures
Texture2D txDiffuse : register(t0);		//color information
Texture2D txNormal : register(t1);		//normal information
SamplerState samLinear : register(s0);	//wrap sampler

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
	float3 Normal : TEXCOORD1;
	float3 Tangent : TEXCOORD2;
	float3 Bitangent : TEXCOORD3;
	float3 World : TEXCOORD4;
};
struct PS_OUTPUT
{
	float4 World : SV_TARGET0;
	float4 Diffuse : SV_TARGET1;
	float4 Normal : SV_TARGET2;
};
//vertex shader
PS_INPUT VS(VS_INPUT input)
{
	float4x4 WorldViewProj = mul(World, mul(View, Projection));
	PS_INPUT output = (PS_INPUT)0;
	output.Pos = mul(input.Pos, WorldViewProj);
	output.Tex = input.Tex;
	//fetch normal and tangent and calculate bitangent
	output.Normal = normalize(mul(input.Normal, (float3x3)World));
	output.Tangent = normalize(mul(input.Tangent, (float3x3)World));
	output.Bitangent = cross(output.Tangent, output.Normal);
	//calculate world output
	float3 world = mul(input.Pos, World).xyz;
	output.World = WorldToTex(world, EyePos, FarPlane);
	return output;
}
//pixel shader
PS_OUTPUT PS(PS_INPUT input)
{
	PS_OUTPUT output = (PS_OUTPUT)0;
	//store world data in World texture
	output.World = float4(input.World, 1);
	//store color data in Diffuse texture
	output.Diffuse = txDiffuse.Sample(samLinear, input.Tex);
	//calculate normal from tangent space and bump mapping data
	float3 texNormal = txNormal.Sample(samLinear, input.Tex).xyz;
	texNormal = normalize(TexToVec(texNormal));
	float3x3 TBN = transpose(float3x3(normalize(input.Bitangent), normalize(input.Normal), normalize(input.Tangent)));
	//store normals in Normal texture
	output.Normal = float4(VecToTex(mul(TBN, texNormal)), 1);
	return output;
}
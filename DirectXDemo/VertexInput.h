//this is an include file for rendering the scene
cbuffer CameraBuffer : register(b0)
{
	matrix View;
	matrix Projection;
	float3 EyePos;
	float FarPlane;
}
cbuffer ModelBuffer : register(b1)
{
	matrix World;
}
struct VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
};
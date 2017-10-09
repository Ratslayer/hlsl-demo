#include "VertexInput.h"
//depth effect that is used for rendering world from light's point of view
//vertex shader that passes only transformed position
float4 VS(VS_INPUT input) : SV_POSITION
{
	float4x4 WorldViewProj = mul(World, mul(View, Projection));
	float4 result = mul(input.Pos, WorldViewProj);
	return result;
}
//pixel shader that renders position to target
float4 PS(float4 Pos : SV_POSITION) : SV_Target
{
	float3 depth = Pos.z;
	return float4(depth, 1);
}
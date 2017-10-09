#include "QuadVertexShader.hlsl"
Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);
//simple draw texture shader
//mostly used for copying targets and debugging
float4 PS(PS_INPUT input) : SV_Target
{
	return txDiffuse.Sample(samLinear, input.Tex);
}
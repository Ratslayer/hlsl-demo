//this is a vertex shader file for post-processing effects
struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
};

PS_INPUT VS(uint id : SV_VERTEXID)
{
	PS_INPUT output = (PS_INPUT)0;
	//calculate position and tex coords from the indices
	output.Tex = float2(id & 1, id >> 1);
	output.Pos = float4((output.Tex.x - 0.5f) * 2, -(output.Tex.y - 0.5f) * 2, 0, 1);

	return output;
}
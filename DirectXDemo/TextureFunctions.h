//this is an include with various texture helper functions
//store normalized vector data in a texture
float3 VecToTex(float3 vec)
{
	return vec * 0.5f + 0.5f;
}
//read normalized vector data from a texture
float3 TexToVec(float3 tex)
{
	return (tex - 0.5f) * 2;
}
//store non-normalized texture data in a texture
float3 WorldToTex(float3 world, float3 Eye, float farPlane)
{
	return VecToTex((world - Eye) / farPlane);
}
//read non-normalized texture data in a texture
float3 TexToWorld(float3 tex, float3 Eye, float farPlane)
{
	return TexToVec(tex) * farPlane + Eye;
}
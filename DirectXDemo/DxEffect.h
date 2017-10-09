#pragma once
#include "main.h"
#include "DxVertexShader.h"
#include "DxPixelShader.h"
//This is a class that contains shader information needed to make a pass
//It can read shader code from 1 or 2 files
class DxEffect
{
public:
	DxEffect(std::wstring fileName);
	DxEffect(std::wstring vsFileName, std::wstring psFileName);
	~DxEffect();

	std::shared_ptr<DxVertexShader> VertexShader;
	std::shared_ptr<DxPixelShader> PixelShader;
	//this function binds both shaders to the pipeline
	void Apply();
private:
	//generic template function to reduce code duplication when creating various shaders
	template<typename ShaderType> std::shared_ptr<ShaderType> LoadShader(std::wstring fileName)
	{
		std::shared_ptr<ShaderType> result = std::shared_ptr<ShaderType>(new ShaderType());
		result->LoadFromFile(fileName);
		return result;
	}

};


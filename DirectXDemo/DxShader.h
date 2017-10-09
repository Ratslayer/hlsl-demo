#pragma once
#include "main.h"
//This is an abstract template class that can be extended to define any type of shader
//This class can read and compile shader code from files
template<typename ShaderType> class DxShader
{
public:
	DxShader() {};
	~DxShader() {};
	//initialization function for the shader
	void LoadFromFile(std::wstring fileName)
	{
		if (!fileName.empty())
		{
			//read data
			ComPtr<ID3DBlob> shaderData = CompileShader(fileName);
			//call child specific virtual function to process data that has been read
			CreateShader(shaderData);
		}
		else
		{
			shader = ComPtr<ShaderType>(nullptr);
		}
	}
	ComPtr<ShaderType> GetShader()
	{
		return shader;
	}
	//This function needs to be implemented for the shader to be properly bound to the pipeline
	virtual void Apply() = 0;
protected:
	std::string type;
	std::string model;
	ComPtr<ShaderType> shader;
	//This function needs to be implemented for the shader to be created from the shader data blob that is read from the file
	virtual void CreateShader(ComPtr<ID3DBlob> shaderData) = 0;
private:
	ComPtr<ID3DBlob> DxShader::CompileShader(std::wstring fileName)
	{
		HRESULT hr = S_OK;
		ComPtr<ID3DBlob> result;
		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
		dwShaderFlags |= D3DCOMPILE_DEBUG;
		dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		ComPtr<ID3DBlob> pErrorBlob;
		hr = D3DCompileFromFile(
			fileName.c_str(),
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			type.c_str(),
			model.c_str(),
			dwShaderFlags,
			0,
			&result,
			&pErrorBlob);
		std::string errorMsgs;
		if (pErrorBlob)
		{
			errorMsgs = reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer());
		}
		ASSERT_HR(hr, "Failed to compile " + StringUtils::ConvertToString(fileName) + ". Errors: " + errorMsgs);
		return result;
	}
};


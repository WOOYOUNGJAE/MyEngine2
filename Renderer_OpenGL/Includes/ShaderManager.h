#pragma once
#include "enums.h"

class CShaderObjectBase;

class CShaderFactory
{
public:
	/**
	 * @param eShaderProgramType Index Compiled Program Stored to
	 * @param szShaderName ..Path/V(F)S_[szShaderName].glsl
	 * @return Created ShaderObject
	 */
	static CShaderObjectBase* Create_Shader(UINT eShaderProgramType, const char* szShaderName);
private:
	static char* readShaderSource(const char* szFilePath);
	static const char* szShaderAssetPath; // Relative path from "App" Dir
};

class CShaderManager : public IUnknown
{
	COM_BASE
public:
	CShaderManager() = default;
	~CShaderManager();
public:
	/**
	 * @param eShaderProgramType Index Compiled Program Stored to
	 * @param szShaderName ..Path/V(F)S_[szShaderName].glsl
	 * @return If Success
	 */
	bool Load_Shader(UINT eShaderProgramType, const char* szShaderName);

public:
	std::map<UINT, CShaderObjectBase*> m_mapShaderObjects;
private:
};


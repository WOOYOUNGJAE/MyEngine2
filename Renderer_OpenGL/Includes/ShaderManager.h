#pragma once
#include "enums.h"

class CShaderObject;
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
private:
	char* readShaderSource(const char* szFilePath);

public:
	std::map<UINT, CShaderObject*> m_mapShaderObjects;
private:
	static const char* szShaderAssetPath; // Relative path from "App" Dir
};


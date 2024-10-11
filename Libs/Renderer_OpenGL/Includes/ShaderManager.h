#pragma once
#include "enums.h"

class CShaderManager : public IUnknown
{
	COM_BASE
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
	GLuint m_ShaderPrograms[Renderer_OpenGL::GL_SHADER_PROGRAM_TYPE::NUM]{};
private:
	static const char* szShaderAssetPath; // Relative path from "App" Dir
};


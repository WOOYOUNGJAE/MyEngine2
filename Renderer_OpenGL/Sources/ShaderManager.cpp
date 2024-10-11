#include "pch.h"
#include "ShaderManager.h"
#include "filesystem"
#include "RendererConfig.h"

IMPL_COM_FUNC(CShaderManager)

const char* CShaderManager::szShaderAssetPath = "..\\Libs\\Renderer_OpenGL\\Shaders\\";

char* CShaderManager::readShaderSource(const char* szFilePath)
{
	FILE* fp = nullptr;

	errno_t err = fopen_s(&fp, szFilePath, "r");

	char errorMsg[256]; // 오류 메시지를 저장할 버퍼
	strerror_s(errorMsg, sizeof(errorMsg), err); // 오류 메시지 복사
	if (err || fp == NULL) { std::cerr << "Reading Shader: " << errorMsg << std::endl; return NULL; }

	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);

	fseek(fp, 0L, SEEK_SET);
	char* buf = new char[size + 1];
	for (int i = 0; i < size + 1; i++) buf[i] = 0;

	fread(buf, 1, size, fp);

	buf[size] = '\0';
	fclose(fp);

	return buf;
}


bool CShaderManager::Load_Shader(UINT eShaderProgramType, const char* szShaderName)
{
	GLuint program = glCreateProgram();

	// Only Use VS, FS
	if (eShaderProgramType < (UINT)GL_SHADER_PROGRAM_TYPE::VS_FS_AND_MORE_NO_USE_YET)
	{
		GLenum  shaderType = GL_VERTEX_SHADER;
		GLchar* source =  nullptr;
		char szFilePath[256]{};
		sprintf_s(szFilePath, 256, szShaderAssetPath);

		for (UINT i = 0; i < 2; ++i)
		{
			GLuint shader = 0;
			char szRealFileName[64]{};
			if (i == 0) // VS
			{
				shader = glCreateShader(GL_VERTEX_SHADER);
				sprintf_s(szRealFileName, 64, "VS_%s.glsl", szShaderName);
			}
			else if (i == 1) // FS
			{
				shader = glCreateShader(GL_FRAGMENT_SHADER);
				sprintf_s(szRealFileName, 64, "FS_%s.glsl", szShaderName);				
			}
			sprintf_s(szFilePath, 256, "%s%s", szFilePath, szRealFileName);
			source = readShaderSource(szFilePath);
			glShaderSource(shader,1, (const GLchar**)&source, NULL);
			glCompileShader(shader);

			GLint  compiled;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
			if (!compiled) {
				std::cerr << szFilePath << " failed to compile:" << std::endl;
				GLint  logSize;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
				char* logMsg = new char[logSize];
				glGetShaderInfoLog(shader, logSize, NULL, logMsg);
				std::cerr << logMsg << std::endl;
				delete[] logMsg;

				return FALSE;
			}
		}
	}

	/* link  and error check */
	glLinkProgram(program);

	GLint  linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked) {
		std::cerr << "Shader program failed to link" << std::endl;
		GLint  logSize;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
		char* logMsg = new char[logSize];
		glGetProgramInfoLog(program, logSize, NULL, logMsg);
		std::cerr << logMsg << std::endl;
		delete[] logMsg;

		return FALSE;
	}

	m_ShaderPrograms[(GL_SHADER_PROGRAM_TYPE)eShaderProgramType] = program;

	return TRUE;
}

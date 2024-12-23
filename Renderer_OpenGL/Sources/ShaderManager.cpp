#include "pch.h"
#include "ShaderManager.h"
#include "filesystem"
#include "RendererConfig.h"
#include "ShaderObject.h"
#include "enums.h"

IMPL_COM_FUNC(CShaderManager)

const char* CShaderFactory::szShaderAssetPath = "..\\Libs\\Renderer_OpenGL\\Shaders\\";

CShaderObjectBase* CShaderFactory::Create_Shader(UINT eShaderProgramType, const char* szShaderName)
{
	GLuint program = glCreateProgram();

	// Only Use VS, FS
	if (eShaderProgramType < (UINT)Renderer_OpenGL::GL_SHADER_PROGRAM_TYPE::VS_FS_AND_MORE_NO_USE_YET)
	{
		GLenum  shaderType = GL_VERTEX_SHADER;
		GLchar* source = nullptr;

		for (UINT i = 0; i < 2; ++i)
		{
			char szFilePath[256]{};
			sprintf_s(szFilePath, 256, szShaderAssetPath);
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
			glShaderSource(shader, 1, (const GLchar**)&source, NULL);
			CHECK_GL_ERROR
				glCompileShader(shader);
			CHECK_GL_ERROR

				GLint  compiled;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
			CHECK_GL_ERROR
				if (!compiled) {
					std::cerr << szFilePath << " failed to compile:" << std::endl;
					GLint  logSize;
					glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
					char* logMsg = new char[logSize];
					glGetShaderInfoLog(shader, logSize, NULL, logMsg);
					std::cerr << logMsg << std::endl;
					delete[] logMsg;

					delete[] source;
					return FALSE;
				}
			glAttachShader(program, shader);
			delete[] source;
		}
	}
	CHECK_GL_ERROR
		/* link  and error check */
		glLinkProgram(program);
	CHECK_GL_ERROR

		GLint  linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	CHECK_GL_ERROR
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

	CShaderObjectBase* pShaderObject = nullptr;
	switch (eShaderProgramType)
	{
	case Renderer_OpenGL::GL_SHADER_PROGRAM_TYPE::SIMPLE:
		pShaderObject = new CShaderObject_Simple(program, szShaderName);
		break;
	case Renderer_OpenGL::GL_SHADER_PROGRAM_TYPE::IMAGE_COPY:
		pShaderObject = new CShaderObject_ImageCopy(program, szShaderName);
		break;
	}

	return pShaderObject;

}


char* CShaderFactory::readShaderSource(const char* szFilePath)
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

CShaderManager::~CShaderManager()
{
	for (auto& iterShaderObject : m_mapShaderObjects)
	{
		RELEASE_INSTANCE(iterShaderObject.second);
	}
}

bool CShaderManager::Load_Shader(UINT eShaderProgramType, const char* szShaderName)
{
	bool bResult = true;
	CShaderObjectBase* pShaderInstance = CShaderFactory::Create_Shader(eShaderProgramType, szShaderName);

	if (pShaderInstance == nullptr)
		bResult = false;

	m_mapShaderObjects.emplace(eShaderProgramType, pShaderInstance);

	return bResult;
}

#include "pch.h"
#include "ShaderObject.h"

IMPL_COM_FUNC(CShaderObject)
GLuint      m_Shader = 0;

CShaderObject::CShaderObject(GLuint shaderProgram, const char* szShaderName) : m_ShaderProgram(shaderProgram), m_strName(std::string(szShaderName))
{
}

void CShaderObject::Bind()
{
	glUseProgram(m_ShaderProgram); // Bind Shader Program


}

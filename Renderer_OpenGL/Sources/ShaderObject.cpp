#include "pch.h"
#include "ShaderObject.h"

IMPL_COM_FUNC(CShaderObjectBase)
GLuint      m_Shader = 0;

CShaderObjectBase::CShaderObjectBase(GLuint shaderProgram, const char* szShaderName) : m_ShaderProgram(shaderProgram), m_strName(std::string(szShaderName))
{
}

CShaderObjectBase::~CShaderObjectBase()
{
}
CShaderObject_Simple::CShaderObject_Simple(GLuint shaderProgram, const char* szShaderName) : CShaderObjectBase(shaderProgram, szShaderName)
{
}

CShaderObject_Simple::~CShaderObject_Simple()
{
}

void CShaderObject_Simple::Set_UniformValue(UINT iUniformIndex, const glm::mat4x4& m)
{
	GLuint uniformModel = 0;
	switch ((UniformEnum)iUniformIndex)
	{
	case ViewProj:
		uniformModel = glGetUniformLocation(m_ShaderProgram, "g_ViewProj");
		break;
	case Model:
		uniformModel = glGetUniformLocation(m_ShaderProgram, "g_Model");
		break;
	default:
		std::cerr << "Uniform Type Error" << std::endl;
	}

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(m)); // row major
}

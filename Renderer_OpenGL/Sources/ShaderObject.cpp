#include "pch.h"
#include "ShaderObject.h"

IMPL_COM_FUNC(CShaderObject)
GLuint      m_Shader = 0;
INT CShaderObject::Initialize(const string& strName, const string& str_VSCode/*loaded String code*/, const string& str_PSCode)
{
	INT iResult = 0; // OK

	m_strName = strName;

	// Compile Shaders
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);




	return iResult;
}

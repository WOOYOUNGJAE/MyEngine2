#pragma once


class CShaderObject : public IUnknown
{
	COM_BASE
public:
	CShaderObject() = delete;
	CShaderObject(GLuint shaderProgram, const char* szShaderName);
	~CShaderObject() = default;
public: // getter
	GLuint Shader() { return m_ShaderProgram; }
	void Bind();

private:
	GLuint      m_ShaderProgram = 0;
	std::string m_strName = "";
	//bool        m_bActive = false;
};
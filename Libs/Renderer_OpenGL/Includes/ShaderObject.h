#pragma once


class CShaderObjectBase : public IUnknown
{
	COM_BASE
public:
	CShaderObjectBase() = delete;
	CShaderObjectBase(GLuint shaderProgram, const char* szShaderName);
	virtual ~CShaderObjectBase();
public: // getter
	GLuint Shader() { return m_ShaderProgram; }
	void Bind() { glUseProgram(m_ShaderProgram); };
	void UnBind() { glUseProgram(0); };
	/**
	 * @param iUniformIndex Which index Uniform in the shader
	 * @param m Matrix
	 */
	virtual void Set_UniformValue(UINT iUniformIndex, const glm::mat4x4& m) = 0;
protected:
	GLuint      m_ShaderProgram = 0;
	std::string m_strName = "";
	//bool        m_bActive = false;
};


class CShaderObject_Simple : public CShaderObjectBase
{
public: enum UniformEnum { ViewProj, Model, Num};
public:
	CShaderObject_Simple() = delete;
	CShaderObject_Simple(GLuint shaderProgram, const char* szShaderName);
	~CShaderObject_Simple() override;
public:
	void Set_UniformValue(UINT iUniformIndex, const glm::mat4x4& m) override;
};
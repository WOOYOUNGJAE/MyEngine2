#pragma once

using std::string;
class CShaderObject : public IUnknown
{
	COM_FUNC

public:
	/**
	 * @param strName Name of This Shader
	 * @param str_VSCode Loaded Vertex Shader Code
	 * @param str_PSCode Loaded Frag Shader Code
	 * @return Result
	 */
	INT Initialize(const string& strName,
	               const string& str_VSCode,
	               const string& str_PSCode);
public: // getter
	GLuint Shader() { return m_Shader; }


private:
	GLuint      m_Shader = 0;
	std::string m_strName = "";
	bool        m_Active = false;
};


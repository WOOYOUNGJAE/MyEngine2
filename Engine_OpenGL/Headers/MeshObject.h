#pragma once
#include "EngineInterface.h"

class CShaderObject;
class CRenderer;
using std::string;
class CMeshObject : public IMeshObject
{
	COM_IMPL
public:
	CMeshObject() = default;
	~CMeshObject() = default;
public:
	void Initialize(CRenderer* pRenderer);
	
private:
	string m_strName = "";
	GLuint m_VBO = 0;
	GLuint m_VAO = 0;
	CShaderObject* m_pShaderObj = nullptr;
private: // pointer
	CRenderer* m_pRenderer = nullptr;
};
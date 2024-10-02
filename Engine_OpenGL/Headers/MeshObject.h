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
	void Begin_CreateMesh(void* pData) override;
	void End_CreateMesh(void* pData) override{};
protected:
	string m_strName = "";
	GLuint m_VBO = 0;
	GLuint m_VAO = 0;
	CShaderObject* m_pShaderObj = nullptr;
protected: // pointer
	CRenderer* m_pRenderer = nullptr;
};
#pragma once
#include "Renderer_Common/Includes/RendererInterface.h"
#include "RendererConfig.h"

class CShaderObject;
class CRenderMachine;
using std::string;

/**
 * @brief Inherit Based on Vertex Type
 */
class RendererOPENGL_DLL CMeshObject : public IMeshObject
{
	COM_FUNC
public:
	CMeshObject() = default;
	~CMeshObject() override;
public:
	void Initialize(CRenderMachine* pRenderMachine);
	void Begin_CreateMesh(void* pData) override;
	void End_CreateMesh(void* pData) override;
public: // getter
	GLuint VBO() { return m_VBO; }
	GLuint VAO() { return m_VAO; }
	GLuint EBO() { return m_EBO; }
protected:
	string m_strName;
	GLuint m_VBO = 0;
	GLuint m_VAO = 0;
	GLuint m_EBO = 0;
	CShaderObject* m_pShaderObj = nullptr;
protected: // Vertex Info
	GL::VertexType* m_pVertexArr;
	GLsizei m_iVertexStride = 0;
protected: // pointer
	CRenderMachine* m_pRenderMachine = nullptr;
};
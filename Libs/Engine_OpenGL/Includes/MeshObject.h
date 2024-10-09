#pragma once
#include "Engine_Common/Includes/EngineInterface.h"
#include "EngineConfig.h"
class CShaderObject;
class CRenderer;
using std::string;

/**
 * @brief Inherit Based on Vertex Type
 */
class ENGINEOPENGL_DLL CMeshObject : public IMeshObject
{
	COM_FUNC
public:
	CMeshObject() = default;
	~CMeshObject() override;
public:
	void Initialize(CRenderer* pRenderer);
	void Begin_CreateMesh(void* pData) override;
	void End_CreateMesh(void* pData) override;
protected:
	string m_strName = "";
	GLuint m_VBO = 0;
	GLuint m_VAO = 0;
	GLuint m_EBO = 0;
	CShaderObject* m_pShaderObj = nullptr;
protected: // Vertex Info
	GL::VertexType* m_pVertexArr;
	GLsizei m_iVertexStride = 0;
protected: // pointer
	CRenderer* m_pRenderer = nullptr;
};
#pragma once
#include "Renderer_Common/Includes/RendererInterface.h"
#include "RendererConfig.h"
#include "enums.h"

class CShaderObject;
class CRenderer;
using std::string;

/**
 * @brief Inherit Based on Vertex Type
 */
class RENDEREROPENGL_DLL CMeshObject : public IMeshObject
{
	COM_BASE
public:
	CMeshObject() = default;
	~CMeshObject() override;
public:
	void Initialize(CRenderer* pRenderer);
	void Begin_CreateMesh(void* pData) override;
	void End_CreateMesh(void* pData) override;
public: // getter
	GLuint VBO() { return m_VBO; }
	GLuint VAO() { return m_VAO; }
	GLuint EBO() { return m_EBO; }
	UINT ShaderType() { return m_eShaderType; }
	UINT NumIndices() { return NumIndices(); }
protected:
	string m_strName;
	GLuint m_VBO = 0;
	GLuint m_VAO = 0;
	GLuint m_EBO = 0;
	/**
	 * Passed to RenderQueue In Render_MeshObject_Client() with "this"
	 */
	UINT m_eShaderType = Renderer_OpenGL::GL_SHADER_PROGRAM_TYPE::NUM;
	UINT m_iNumIndices = 0;
protected: // Vertex Info
	GL::VertexType* m_pVertexArr;
	GLsizei m_iVertexStride = 0;
protected: // pointer
	CRenderer* m_pRenderer = nullptr;
};
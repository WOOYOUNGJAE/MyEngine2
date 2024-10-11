#pragma once
#include "RendererConfig.h"
#include "Renderer_Common/Includes/RendererInterface.h"
#include "Viewer.h"

struct GLFWwindow;
class CViewer;
class CShaderManager;
/**
 * @brief Top-level class. All GL-Dependant Classes should be in this project
 */
class RENDEREROPENGL_DLL CRenderer final : public IRenderer
{
	COM_BASE
public:
	CRenderer() = delete;
	CRenderer(IRenderer::OpenGL identifier, UINT uiWinX, UINT uiWinY, const char* szTitle);
	~CRenderer();
public:
	void Initialize(void*) override;
	/**
	 * @return If WindowShouldClose
	 */
	INT MainRender(FLOAT fDeltaTime) override;
	void BeginRender() override;
	void Render_MeshObject(IMeshObject* pMeshObj) override;
	void EndRender() override;

	// getter
	//IRenderMachine* Get_RenderMachine() override;
	
	IMeshObject* Create_EmptyBasicMesh(void* pData) override;
	IMeshObject* Create_EmptyColoredMesh(void* pData) override;
private:
	GLFWwindow* m_pWindow = nullptr;
	CViewer* m_pViewer = nullptr;
private: //Managers
	CShaderManager* m_pShaderManager = nullptr;
};
#pragma once
#include "RendererConfig.h"
#include "Renderer_Common/Includes/RendererInterface.h"
#include "Viewer.h"

class CViewer;
struct GLFWwindow;
/**
 * @brief Top-level class
 */
class RENDEREROPENGL_DLL CRenderer final : public IRenderer
{
	COM_BASE
public:
	CRenderer() = delete;
	CRenderer(IRenderer::OpenGL identifier, UINT uiWinX, UINT uiWinY, const char* szTitle);
	~CRenderer();
public:
	HRESULT Initialize(void*) override;
	/**
	 * @return If WindowShouldClose
	 */
	INT Renderer_Tick(FLOAT fDeltaTime) override;
	void BeginRender() override;
	void MainRender() override;
	void Render_MeshObject(IMeshObject* pMeshObj) override;
	void EndRender() override;

	// getter
	//IRenderMachine* Get_RenderMachine() override;
	
	IMeshObject* Create_EmptyBasicMesh(void* pData) override;
	IMeshObject* Create_EmptyColoredMesh(void* pData) override;
private:
	GLFWwindow* m_pWindow = nullptr;
	CViewer* m_pViewer = nullptr;
	//IRenderMachine* m_pRenderer = nullptr;
};
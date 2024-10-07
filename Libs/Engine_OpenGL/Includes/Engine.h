#pragma once
#include "EngineConfig.h"
#include "EngineInterface.h"
#include "Viewer.h"

class CViewer;
struct GLFWwindow;
/**
 * @brief Top-level class
 */
class ENGINEOPENGL_DLL CEngine final : public IEngine
{
	COM_FUNC
public:
	CEngine() = delete;
	CEngine(IEngine::OpenGL identifier, UINT uiWinX, UINT uiWinY, const char* szTitle);
	~CEngine();
public:
	HRESULT Initialize(void*) override;
	/**
	 * @return If WindowShouldClose
	 */
	INT Engine_Tick(FLOAT fDeltaTime) override;
	void BeginRender() override;
	void MainRender() override;
	void EndRender() override;
	
	IMeshObject* Create_EmptyColoredMesh(void* pData) override;
private:
	GLFWwindow* m_pWindow = nullptr;
	CViewer* m_pViewer = nullptr;
};
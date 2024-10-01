#pragma once
#include "Engine_OpenGL/EngineConfig.h"
#include "EngineInterface.h"
#include "Viewer.h"

class CViewer;
struct GLFWwindow;
/**
 * @brief Top-level class
 */
class ENGINEOPENGL_DLL CEngine final : public IEngine
{
public:
	CEngine() = delete;
	CEngine(IEngine::OpenGL identifier, UINT uiWinX, UINT uiWinY, const char* szTitle);
	~CEngine() override;
public:
	/**
	 * @return If WindowShouldClose
	 */
	INT Engine_Tick(BOOL bShouldClose, FLOAT fDeltaTime) override;

private:
	GLFWwindow* m_pWindow = nullptr;
	CViewer* m_pViewer = nullptr;
};
#pragma once
#include "Engine_OpenGL/EngineConfig.h"
#include "Defines.h"
#include "EngineInterface.h"

class CViewer;
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
	void Engine_Tick(FLOAT fDeltaTime) override;

private:
	CViewer* m_pViewer = nullptr;
};
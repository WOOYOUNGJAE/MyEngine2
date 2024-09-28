#pragma once
#include "Engine_OpenGL/EngineConfig.h"
#include "Defines.h"
#include "RendererInterface.h"

class ENGINEOPENGL_DLL CRenderer : public IRenderer
{
public:
	CRenderer() = delete;
	CRenderer(IRenderer::OpenGL identifier, UINT uiWinX, UINT uiWinY, const char* szTitle);
	~CRenderer() override;

};
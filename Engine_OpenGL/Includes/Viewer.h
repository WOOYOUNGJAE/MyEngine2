#pragma once

class CRenderTarget;
struct GLFWwindow;
/**
 * Member: Scene, Renderer, RenderTargets \n
 * Func: Bind, Unbind, OnRender, ...
 */
class CViewer
{
public:
	CViewer(UINT uiWinX, UINT uiWinY);
	~CViewer();

public:
	void BeginRender();
	void MainRender();
	void EndRender(GLFWwindow* pWindow);
public:
	void On_Resize_Window(UINT uiWinX, UINT uiWinY);
private:
	UINT m_uiWinX = 0;
	UINT m_uiWinY = 0;
	CRenderTarget* m_pRenderTarget = nullptr;
};


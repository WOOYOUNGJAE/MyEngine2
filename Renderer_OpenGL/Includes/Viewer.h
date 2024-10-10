#pragma once

class CRenderTarget;
struct GLFWwindow;
class CRenderer;
//interface IRenderMachine;
//class CRenderMachine;
/**
 * Member: Scene, Renderer, RenderTargets \n
 * Func: Bind, Unbind, OnRender, ...
 */
class CViewer
{
public:
	CViewer(UINT uiWinX, UINT uiWinY, CRenderer* pRenderer);
	~CViewer();

public:
	void BeginRender();
	void EndRender(GLFWwindow* pWindow);
public: // getter
	//IRenderMachine* Get_RenderMachine() { return m_pRenderer; }
public:
	void On_Resize_Window(UINT uiWinX, UINT uiWinY);
private:
	UINT m_uiWinX = 0;
	UINT m_uiWinY = 0;
	CRenderTarget* m_pRenderTarget = nullptr;
private: // pointer
	CRenderer* m_pRenderer = nullptr;
	//CRenderMachine* m_pRenderer = nullptr;
};


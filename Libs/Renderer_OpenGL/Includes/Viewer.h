#pragma once

class CRenderTarget;
struct GLFWwindow;
interface IRenderMachine;
class CRenderMachine;
/**
 * Member: Scene, RenderMachine, RenderTargets \n
 * Func: Bind, Unbind, OnRender, ...
 */
class CViewer
{
public:
	CViewer(UINT uiWinX, UINT uiWinY, IRenderMachine* pInRenderMachine);
	~CViewer();

public:
	void BeginRender();
	void EndRender(GLFWwindow* pWindow);
public: // getter
	//IRenderMachine* Get_RenderMachine() { return m_pRenderMachine; }
public:
	void On_Resize_Window(UINT uiWinX, UINT uiWinY);
private:
	UINT m_uiWinX = 0;
	UINT m_uiWinY = 0;
	CRenderTarget* m_pRenderTarget = nullptr;
private: // pointer
	CRenderMachine* m_pRenderMachine = nullptr;
};


#pragma once

class CRenderTarget;
struct GLFWwindow;
interface IRenderer;
<<<<<<< HEAD
class CRenderer;
=======
>>>>>>> c4fbfdd2e5b4b3ee1f7bf374bff31862f5f5af1d
/**
 * Member: Scene, Renderer, RenderTargets \n
 * Func: Bind, Unbind, OnRender, ...
 */
class CViewer
{
public:
	CViewer(UINT uiWinX, UINT uiWinY, IRenderer* pInRenderer);
	~CViewer();

public:
	void BeginRender();
	void EndRender(GLFWwindow* pWindow);
public: // getter
<<<<<<< HEAD
	//IRenderer* Get_Renderer() { return m_pRenderer; }
=======
	IRenderer* Get_Renderer() { return m_pRenderer; }
>>>>>>> c4fbfdd2e5b4b3ee1f7bf374bff31862f5f5af1d
public:
	void On_Resize_Window(UINT uiWinX, UINT uiWinY);
private:
	UINT m_uiWinX = 0;
	UINT m_uiWinY = 0;
	CRenderTarget* m_pRenderTarget = nullptr;
<<<<<<< HEAD
private: // pointer
	CRenderer* m_pRenderer = nullptr;
=======
	IRenderer* m_pRenderer = nullptr;
>>>>>>> c4fbfdd2e5b4b3ee1f7bf374bff31862f5f5af1d
};


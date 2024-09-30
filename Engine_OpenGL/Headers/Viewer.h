#pragma once

class CRenderTarget;
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
	void EndRender();
private:
	UINT m_uiWinX = 0;
	UINT m_uiWinY = 0;
	CRenderTarget* m_pRenderTarget = nullptr;
};


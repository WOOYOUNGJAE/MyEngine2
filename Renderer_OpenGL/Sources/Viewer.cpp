#include "pch.h"
#include "Viewer.h"
#include "RenderTarget.h"
#include "Renderer.h"

CViewer::CViewer(UINT uiWinX, UINT uiWinY, CRenderer* pRenderer) : m_uiWinX(uiWinX), m_uiWinY(uiWinY), m_pRenderer(pRenderer)
{
}

CViewer::~CViewer()
{
}

void CViewer::BeginRender()
{
	glViewport(0, 0, (UINT)m_uiWinX, (UINT)m_uiWinY);

	glClearColor(37.f / 255.f, 37.f / 255.f, 38.f / 255.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void CViewer::EndRender(GLFWwindow* pWindow)
{
	glfwSwapBuffers(pWindow);
}

void CViewer::On_Resize_Window(UINT uiWinX, UINT uiWinY)
{
	m_uiWinX = uiWinX;
	m_uiWinY = uiWinY;
}

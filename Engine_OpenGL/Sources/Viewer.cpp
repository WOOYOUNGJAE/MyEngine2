#include "pch.h"
#include "Viewer.h"
#include "RenderTarget.h"

CViewer::CViewer(UINT uiWinX, UINT uiWinY) : m_uiWinX(uiWinX), m_uiWinY(uiWinY)
{
}

CViewer::~CViewer()
{
}

void CViewer::BeginRender()
{
	glViewport(0, 0, (INT)m_uiWinX, (INT)m_uiWinY);

}

void CViewer::MainRender()
{
}

void CViewer::EndRender()
{
}

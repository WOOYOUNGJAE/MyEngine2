#include "pch.h"
#include "InputManager.h"
#include "Renderer_OpenGL/Includes/Renderer.h"

CInputManager* g_Input = nullptr;

IMPL_COM_FUNC(CInputManager)
IMPLEMENT_SINGLETON(CInputManager)

CInputManager::CInputManager()
{
	if (g_Input == nullptr)
	{
		g_Input = this;
	}
}

CInputManager::~CInputManager()
{
	RELEASE_INSTANCE(m_pGLRenderer);
}

void CInputManager::Initialize(HWND* pHwnd, IRenderer* pGLRenderer)
{
	if (pHwnd)
	{
		m_pHwnd = pHwnd;
		return;
	}
	if (pGLRenderer)
	{
		m_pGLRenderer = reinterpret_cast<CRenderer*>(pGLRenderer);

		ADDREF_INSTANCE(m_pGLRenderer);
	}
}

void CInputManager::Tick(HWND* pHwnd)
{
	if (pHwnd == nullptr)
		return;

	for (INT keyChecking = 0; keyChecking < VK_MAX; ++keyChecking)
	{

		if (GetAsyncKeyState(keyChecking) & 0x8000) // 키가 눌리면
		{
			if (m_keyStateArr[keyChecking].first) // 이전에 눌렸다면
			{
				m_keyStateArr[keyChecking].second = KEY_PRESSING; // 누르고 있는 상태
			}
			else
			{
				m_keyStateArr[keyChecking].first = true;
				m_keyStateArr[keyChecking].second = KEY_DOWN;		// 막 누른 상태
			}
		}
		else // 눌리지 않았다면
		{
			if (m_keyStateArr[keyChecking].first) // 이전에 눌렸다면
			{
				m_keyStateArr[keyChecking].first = false;
				m_keyStateArr[keyChecking].second = KEY_UP;
			}
			else
			{
				m_keyStateArr[keyChecking].second = KEY_NONE;
			}
		}
	}

	//Mouse
	m_prevMousePos = m_curMousePos;
	GetCursorPos(&m_curMousePos);
	ScreenToClient(*pHwnd, &m_curMousePos);
}

bool CInputManager::Key_Pressing(int inKey)
{
	bool bResult = m_pHwnd ? m_keyStateArr[inKey].second == KEY_PRESSING : m_pGLRenderer->Key_Pressing(inKey);
	return bResult;
}

bool CInputManager::Key_Down(int inKey)
{
	bool bResult = m_pHwnd ? m_keyStateArr[inKey].second == KEY_DOWN : m_pGLRenderer->Key_Down(inKey);
	return bResult;
}

bool CInputManager::Key_Up(int inKey)
{
	bool bResult = m_pHwnd ? m_keyStateArr[inKey].second == KEY_UP : m_pGLRenderer->Key_Up(inKey);
	return bResult;
}

Vector2 CInputManager::Get_MouseDirPrevToCur()
{
	if (m_pHwnd)
	{
		return Vector2((m_curMousePos.x - m_prevMousePos.x), (m_curMousePos.y - m_prevMousePos.y));;
	}

	if (m_pGLRenderer)
	{
		return Vector2(
			FLOAT(m_pGLRenderer->m_KeyManager.curMousePosXY[0] - m_pGLRenderer->m_KeyManager.prevMousePosXY[0]),
			FLOAT(m_pGLRenderer->m_KeyManager.curMousePosXY[1] - m_pGLRenderer->m_KeyManager.prevMousePosXY[1])
			);
	}

	return Vector2();
}

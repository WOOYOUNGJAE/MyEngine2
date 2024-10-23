#pragma once
#include "EngineConfig.h"

enum KEY_STATE { KEY_NONE, KEY_DOWN, KEY_UP, KEY_PRESSING, KEY_STATE_NUM };

interface IRenderer;
class CRenderer;

class ENGINECORE_DLL CInputManager : public IUnknown
{
static constexpr int VK_MAX = 0xff;
	COM_BASE
	DECLARE_SINGLETON(CInputManager)
public:
	CInputManager();
	~CInputManager();
public:
	void Initialize(HWND* pHwnd, IRenderer* pGLRenderer);
	void Tick(HWND* pHwnd); // WinApi

public: // Get Key State
	bool Key_Pressing(int inKey);
	bool Key_Down(int inKey);
	bool Key_Up(int inKey);
public: // Mouse
	Vector2 Get_MouseDirPrevToCur();

private:
	// first는 단순 OX second는 up down pressing
	std::pair<bool, KEY_STATE> m_keyStateArr[VK_MAX]{};
	POINT m_curMousePos{};
	POINT m_prevMousePos{};
private: // Pointer
	HWND* m_pHwnd = nullptr;
	CRenderer* m_pGLRenderer = nullptr;
};


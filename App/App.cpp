// App.cpp : Defines the entry point for the application.
//
#include "pch.h"
#include "App.h"

#include "Game.h"
#include "Engine_OpenGL/Headers/Engine.h"
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst = nullptr;                                // current instance
HWND g_hMainWindow = nullptr;
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

void RunGame();

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
HWND InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//DeviceResources instance;

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	BYTE* pLeakTest = new BYTE;
#endif

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDI_APP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	AllocConsole();

	FILE* stream_in;
	FILE* stream_out;
	FILE* stream_err;

	freopen_s(&stream_in, "CONIN$", "r", stdin);
	freopen_s(&stream_out, "CONOUT$", "w", stdout);
	freopen_s(&stream_err, "CONOUT$", "w", stderr);

	IEngine* pEngine = nullptr;
	CGame* pGame = new CGame();

	// Select Graphics Api
	enum Graphics { DirectX12, OpenGL, Vulkan, Num };
	INT iGraphics = INT32_MAX;
	INT iRunResult = INT32_MAX;
	std::cout << "Select API\n1.DirectX12, 2.OpenGL\n: ";
	//std::cin >> iGraphics;
	//iGraphics -= 1;
	system("cls");
	iGraphics = OpenGL;

	UINT uiWinX = 1280, uiWinY = 720;

	char strTitle[MAX_LOADSTRING];
	WideCharToMultiByte(CP_UTF8, 0, szTitle, -1, strTitle, MAX_LOADSTRING, NULL, NULL);
	pGame->Initialize(std::string(strTitle));
	pGame->Run();


	MSG msg; // For Window App
	//if (iGraphics == DirectX12)
	//{
	//	// Perform application initialization:
	//	g_hMainWindow = InitInstance(hInstance, nCmdShow);
	//	if (!g_hMainWindow)
	//	{
	//		FreeConsole();
	//		return FALSE;
	//	}

	//	iRunResult = Run_DirectX12(msg);
	//}
	//else if (iGraphics == OpenGL)
	//{
	//	char strTitle[MAX_LOADSTRING];
	//	WideCharToMultiByte(CP_UTF8, 0, szTitle, -1, strTitle, MAX_LOADSTRING, NULL, NULL);
	//	strcat_s(strTitle, MAX_LOADSTRING, " - OpenGL");
	//	pEngine = new CEngine(IEngine::OpenGL(), uiWinX, uiWinY, strTitle);
	//	iRunResult = Run_OpenGL(pEngine);
	//}
	//else if (iGraphics >= Graphics::Num)
	//{
	//	return FALSE;
	//}



	if (pGame)
	{
		pGame->Release();
	}

#ifdef _DEBUG
	_ASSERT(_CrtCheckMemory());
#endif

	BOOL	bHasMsg = PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);

	if (bHasMsg)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

void RunGame()
{
	//// begin
	//g_pRenderer->BeginRender();

	//// game business logic

	//// rendering objects

	//// end
	//g_pRenderer->EndRender();

	//// Present
	//g_pRenderer->Present();

}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_APP);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable
	
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return nullptr;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			FreeConsole();
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE: // EXIT
			DestroyWindow(hWnd);
			break;
		}

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT Run_DirectX12(MSG& msg)
{

	//HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDI_APP));

	/*g_pRenderer = new CD3D12Renderer;
	g_pRenderer->Initialize(g_hMainWindow, TRUE, TRUE);*/

	// Main message loop:
	while (true)
	{
		// call WndProc
		//g_bCanUseWndProc == FALSE이면 DefWndProc호출

		BOOL	bHasMsg = PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);

		if (bHasMsg)
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//pEngine->Engine_Tick();
		}
	}
	return TRUE;
}

INT Run_OpenGL(IEngine* pEngine)
{
	BOOL bShouldClose = FALSE; // Result of Prev EngineTick
	while (true)
	{
		// Some Acting Change ShouldClose

		// Tick, Render, ...
		bShouldClose = 
			pEngine->Engine_Tick(0.2f);

		if (bShouldClose)
			break;
	}

	return TRUE;
}
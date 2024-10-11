#include "pch.h"
#include "Game.h"

#include "Engine_Core/Includes/Engine_Core.h"
#include "Engine_Core/Includes/Enums.h"

#include "TestGameObj.h"

IMPL_COM_FUNC(CGame)

CTestGameObj* pTestObj;
CGame::~CGame()
{
	RELEASE_INSTANCE(m_pEngine);
}

HRESULT CGame::Initialize(std::string& strTitle)
{
	HRESULT hr = S_OK;

	// Select Graphics Api
	enum Graphics { DirectX12, OpenGL, Vulkan, Num };
	INT iGraphics = INT32_MAX;
	std::cout << "Select API\n1.DirectX12, 2.OpenGL\n: ";
	//std::cin >> iGraphics;
	//iGraphics -= 1;
	system("cls");
	iGraphics = OpenGL;

	m_pEngine = new CEngine_Core();
	m_pEngine->Initialize(iGraphics, strTitle);


	// Init Scene (Temp)
	pTestObj = new CTestGameObj();
	pTestObj->Initialize(m_pEngine);

	m_pEngine->Add_GameObj(Engine_Core::GAME_OBJ_LIST_TYPE::DEFAULT, pTestObj);
	return hr;
}

void CGame::Run()
{
	while (m_pEngine->Run());
}

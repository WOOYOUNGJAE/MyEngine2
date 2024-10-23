#include "pch.h"
#include "Engine_Core.h"

#include "Camera.h"
#include "Renderer_Common/Includes/PrimitiveGeomtryGenerator.h"
#include "Renderer_Common/Includes/Structs.h"
#include "Renderer_Common/Includes/RendererInterface.h"

#include "Renderer_OpenGL/Includes/Renderer.h"

#include "GameObjectManager.h"
#include "InputManager.h"
IMPL_COM_FUNC(CEngine_Core)

CEngine_Core::~CEngine_Core()
{
	RELEASE_INSTANCE(m_pInputManager);
	RELEASE_INSTANCE(m_pGameObjManager);
	RELEASE_INSTANCE(m_pRenderer);
}

void CEngine_Core::Initialize(INT iGraphics, std::string& strTitle)
{

#pragma region Create_Renderer
	// Select Graphics Api
	enum Graphics { DirectX12, OpenGL, Vulkan, Num };
	iGraphics = OpenGL;

	UINT uiWinX = 1280, uiWinY = 720;


	if (iGraphics == OpenGL)
	{
		strTitle += " - OpenGL";
		m_pRenderer = new CRenderer(IRenderer::OpenGL(), uiWinX, uiWinY, strTitle.c_str(), &m_pGLWin);
	}
	else if (iGraphics >= Graphics::Num)
	{
		return;
	}
	m_pRenderer->Initialize();
#pragma endregion

	m_pGameObjManager = new CGameObjectManager();
	m_pInputManager = CInputManager::Get_Instance();
	m_pInputManager->Initialize(m_pHwnd, m_pRenderer);
	
}

BOOL CEngine_Core::Run()
{
	m_pRenderer->BeginRender();

	// Tick, Render, ...
	
	// Obj Manger Render
	m_pGameObjManager->Tick(0.2f);
	m_pGameObjManager->Late_Tick(0.2f);

	if (m_pHwnd)
	{
		m_pInputManager->Tick(m_pHwnd);
	}
	else if (m_pGLWin)
	{
	}

	m_pGameObjManager->Render();

	// Renderer Render
	m_pRenderer->Update_CameraInfo(m_pCamera->m_pTransform.WorldMatrix(), m_pCamera->m_CamDesc);
	

	if (m_pRenderer->MainRender(0.2f) == FALSE)
		return FALSE;

	m_pRenderer->EndRender();

	return TRUE;
}

void CEngine_Core::Add_GameObj(UINT eType, CGameObject* pInstance)
{
	m_pGameObjManager->Add_GameObj((Engine_Core::GAME_OBJ_LIST_TYPE)eType, pInstance);
}

void CEngine_Core::Activate_Camera(const std::string& cameraTag)
{
	m_pCamera = m_pGameObjManager->Activate_Camera(cameraTag);	
}

void CEngine_Core::Activate_Camera(CGameObject* pCameraInstance)
{
	m_pCamera = m_pGameObjManager->Activate_Camera(pCameraInstance);
}

#include "pch.h"
#include "Engine_Core.h"

#include "Camera.h"
#include "Common/Includes/PrimitiveGeomtryGenerator.h"
#include "Common/Includes/Structs.h"
#include "Common/Includes/RendererInterface.h"

#include "Renderer_OpenGL/Includes/Renderer.h"

#include "CUDA/Includes/CUDA_Core.h"

#include "GameObjectManager.h"
#include "InputManager.h"
#include "AssetManager.h"

#include "Asset_ply.h"

IMPL_COM_FUNC(CEngine_Core)

Graphics_API g_eGraphicsApi = Graphics_API::Num;
UINT g_uiWinX = 1280, g_uiWinY = 720;
bool g_bReadyCudaCore = true;

CEngine_Core::~CEngine_Core()
{
	RELEASE_INSTANCE(m_pAssetManager);
	RELEASE_INSTANCE(m_pInputManager);
	RELEASE_INSTANCE(m_pGameObjManager);
	RELEASE_INSTANCE(m_pCudaCore);
	RELEASE_INSTANCE(m_pRenderer);
}

void CEngine_Core::Initialize(INT iGraphics, std::string& strTitle)
{

#pragma region Create_Renderer
	// Select Graphics_API Api
	iGraphics = OpenGL;
	g_eGraphicsApi = (Graphics_API)iGraphics;

	UINT uiWinX = g_uiWinX, uiWinY = g_uiWinY;


	if (iGraphics == OpenGL)
	{
		strTitle += " - OpenGL";
		m_pRenderer = new CRenderer(IRenderer::OpenGL(), uiWinX, uiWinY, strTitle.c_str(), &m_pGLWin);
	}
	else if (iGraphics >= Graphics_API::Num)
	{
		return;
	}
	bool bReadyCudaCore = g_bReadyCudaCore;
	m_pRenderer->Initialize(&bReadyCudaCore);
#pragma endregion

	// Cuda
	if (bReadyCudaCore)
	{
		m_pCudaCore = new CCUDA_Core(m_pRenderer, uiWinX, uiWinY);		
	}

	// Create Managers
	m_pGameObjManager = new CGameObjectManager();

	m_pInputManager = CInputManager::Get_Instance();
	m_pInputManager->Initialize(m_pHwnd, m_pRenderer);

	m_pAssetManager = new CAssetManager();
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

void CEngine_Core::Add_Ply(const wchar_t* wszPath, CAsset* pAssetInstance)
{
	m_pAssetManager->Add_Ply(wszPath, pAssetInstance);

}

CAsset_ply* CEngine_Core::Get_Ply(const wchar_t* wszPath)
{
	return m_pAssetManager->Get_Ply(wszPath);
}


void CEngine_Core::EndSign_LoadingAllPlys()
{
	// All Loaded ply Asset
	std::map<std::wstring, CAsset_ply*> plyMap = m_pAssetManager->Get_PlyMap();

	UINT iNumAssets = plyMap.size();
	CAsset_ply** pAssetArr = new CAsset_ply*[iNumAssets];

	UINT iArrayIndex = 0;
	for (auto& iterAsset : plyMap)
	{
		pAssetArr[iArrayIndex++] = iterAsset.second;
	}


	m_pCudaCore->Create_CudaResource_GS(pAssetArr, iNumAssets);


	DELETE_ARRAY(pAssetArr);
}

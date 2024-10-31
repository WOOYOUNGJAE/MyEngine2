#pragma once
#include "EngineConfig.h"

interface IRenderer;
interface IMeshObject;
class CGameObject;
class CGameObjectManager;
class CInputManager;
class CAssetManager;
class CCamera;
class CAsset;
class CAsset_ply;
class CCUDA_Core;
class ENGINECORE_DLL CEngine_Core : public IUnknown
{
	COM_BASE
public:
	CEngine_Core() = default;
	~CEngine_Core();
public:
	void Initialize(INT iGraphics, std::string& strTitle);
	/**
	 * @return If Continue Processing
	 */
	BOOL Run();
public: // Manger Funcs
	void Add_GameObj(UINT eType, CGameObject* pInstance);
	void Activate_Camera(const std::string& cameraTag);
	void Activate_Camera(CGameObject* pCameraInstance); // Activate Directly
	void Add_Ply(const wchar_t* wszPath, CAsset* pAssetInstance);
	CAsset_ply* Get_Ply(const wchar_t* wszPath);
public: // Cuda Core
	void EndSign_LoadingAllPlys();
public:
	IRenderer* m_pRenderer = nullptr;
private: // Managers
	CGameObjectManager* m_pGameObjManager = nullptr;
	CInputManager* m_pInputManager = nullptr;
	CAssetManager* m_pAssetManager = nullptr;
private: // pointer
	CCamera* m_pCamera = nullptr;
private: // Windows Pointer
	HWND* m_pHwnd = nullptr;
	GLFWwindow* m_pGLWin = nullptr;
private: // CUDA
	CCUDA_Core* m_pCudaCore = nullptr;
};
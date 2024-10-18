#pragma once

#include "Enums.h"

class CGameObject;
class CCamera;
class CGameObjectManager : public IUnknown
{
	COM_BASE
public:
	CGameObjectManager() = default;
	~CGameObjectManager();

public: // Cycle
	void Tick(FLOAT fDeltaTime);
	void Late_Tick(FLOAT fDeltaTime);
	void Render();
public:
	CCamera* Get_ActiveCam() { return m_pActiveCam; }
	void Add_GameObj(Engine_Core::GAME_OBJ_LIST_TYPE eType, CGameObject* pInstance);
	CCamera* Activate_Camera(const std::string& cameraTag);
	CCamera* Activate_Camera(CGameObject* pCameraInstance); // Activate Directly
private:
	std::list<CGameObject*> m_GameObjListArr[Engine_Core::GAME_OBJ_LIST_TYPE::NUM]; // [List, List, ..]
private: // Pointer
	CCamera* m_pActiveCam = nullptr;
};


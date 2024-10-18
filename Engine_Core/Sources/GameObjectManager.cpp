#include "pch.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Camera.h"

IMPL_COM_FUNC(CGameObjectManager)

CGameObjectManager::~CGameObjectManager()
{
	for (auto& iterList : m_GameObjListArr)
	{
		for (auto& iterGameObj : iterList)
		{
			RELEASE_INSTANCE(iterGameObj);
		}
	}
}


void CGameObjectManager::Tick(FLOAT fDeltaTime)
{
	for (auto& iterList : m_GameObjListArr)
	{
		for (auto& iterGameObj : iterList)
		{
			iterGameObj->Tick(fDeltaTime);
		}
	}
}

void CGameObjectManager::Late_Tick(FLOAT fDeltaTime)
{
	for (auto& iterList : m_GameObjListArr)
	{
		for (auto& iterGameObj : iterList)
		{
			iterGameObj->Late_Tick(fDeltaTime);
		}
	}
}

void CGameObjectManager::Render()
{
	for (UINT i = 0; i < Engine_Core::GAME_OBJ_LIST_TYPE::NUM; ++i)
	{
		if (i == Engine_Core::GAME_OBJ_LIST_TYPE::CAMERA)
			continue;

		for (auto& iterGameObj : m_GameObjListArr[i])
		{
			iterGameObj->Render();			
		}
	}
}

void CGameObjectManager::Add_GameObj(Engine_Core::GAME_OBJ_LIST_TYPE eType, CGameObject* pInstance)
{
	m_GameObjListArr[eType].emplace_back(pInstance);
}

CCamera* CGameObjectManager::Activate_Camera(const std::string& cameraTag)
{
	for (auto& iterObj : m_GameObjListArr[Engine_Core::GAME_OBJ_LIST_TYPE::CAMERA])
	{
		if (iterObj->Get_Tag() == cameraTag)
		{
			m_pActiveCam = dynamic_cast<CCamera*>(iterObj);
			return m_pActiveCam;
		}
	}
	return nullptr;
}

CCamera* CGameObjectManager::Activate_Camera(CGameObject* pCameraInstance)
{
	m_pActiveCam = dynamic_cast<CCamera*>(pCameraInstance);
	return m_pActiveCam;
}

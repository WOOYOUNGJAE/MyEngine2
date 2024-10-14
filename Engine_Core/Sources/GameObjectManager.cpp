#include "pch.h"
#include "GameObjectManager.h"
#include "GameObject.h"

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
	for (auto& iterList : m_GameObjListArr)
	{
		for (auto& iterGameObj : iterList)
		{
			iterGameObj->Render();
		}
	}
}

void CGameObjectManager::Add_GameObj(Engine_Core::GAME_OBJ_LIST_TYPE eType, CGameObject* pInstance)
{
	m_GameObjListArr[eType].push_back(pInstance);
}



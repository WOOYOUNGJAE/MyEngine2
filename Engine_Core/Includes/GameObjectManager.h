#pragma once

#include "Enums.h"

class CGameObject;
class CGameObjectManager : public IUnknown
{
	COM_BASE
public:
	CGameObjectManager() = default;
	~CGameObjectManager();

public:
	void Tick(FLOAT fDeltaTime);
	void Late_Tick(FLOAT fDeltaTime);
	void Add_GameObj(GAME_OBJ_LIST_TYPE eType, CGameObject* pInstance);
private:
	std::list<CGameObject*> m_GameObjListArr[GAME_OBJ_LIST_TYPE::NUM]; // [List, List, ..]
};


#pragma once
#include "EngineConfig.h"

interface IRenderer;
interface IMeshObject;
class CGameObject;
class CGameObjectManager;
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

public:
	IRenderer* m_pRenderer = nullptr;
private:
	CGameObjectManager* m_pGameObjManager = nullptr;

};


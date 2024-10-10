#pragma once

#include "EngineConfig.h"

interface IMeshObject;
interface IRenderer;
class CEngine_Core;
class CGame;
class ENGINECORE_DLL CGameObject : public IUnknown
{
	COM_BASE
public:
	CGameObject() = default;
	virtual ~CGameObject() = default;

public:
	virtual void Initialize(CEngine_Core* pEngine) = 0;
	virtual void Tick(FLOAT fDeltaTime) = 0;
	virtual void Late_Tick(FLOAT fDeltaTime) = 0;
	virtual void Render() = 0;

protected: // Pointer
	IMeshObject* m_pMeshObj = nullptr;
	IRenderer* m_pRenderer = nullptr;
};


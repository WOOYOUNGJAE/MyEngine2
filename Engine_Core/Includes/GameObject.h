#pragma once

#include "EngineConfig.h"
#include "Transform.h"

interface IMeshObject;
interface IRenderer;
class CEngine_Core;
class CGame;
class CTransform;
class ENGINECORE_DLL CGameObject : public IUnknown
{
	COM_BASE
public:
	CGameObject() = default;
	virtual ~CGameObject() = default;

public:
	virtual void Initialize(CEngine_Core* pEngine) = 0;
	virtual void Tick(FLOAT fDeltaTime) = 0;
	virtual void Late_Tick(FLOAT fDeltaTime);
	virtual void Render() = 0;
public:
	std::string Get_Tag() { return m_strTag; }
	void Set_Tag(const std::string& strTag) { m_strTag = strTag; }
public:
	CTransform m_pTransform;
private:
	std::string m_strTag;
protected: // Pointer
	IMeshObject* m_pMeshObj = nullptr;
	IRenderer* m_pRenderer = nullptr;
};


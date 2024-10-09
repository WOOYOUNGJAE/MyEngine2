#pragma once

interface IMeshObject;
interface IRenderMachine;
interface IRenderer;
class CGame;
class CGameObject : public IUnknown
{
	COM_FUNC
public:
	CGameObject() = default;
	virtual ~CGameObject() = default;

public:
	virtual void Initialize(CGame* pGame) = 0;
	virtual void Tick(FLOAT fDeltaTime) = 0;
	virtual void Late_Tick(FLOAT fDeltaTime) = 0;
	virtual void Render() = 0;

protected: // Pointer
	IMeshObject* m_pMeshObj = nullptr;
	IRenderMachine* m_pRenderMachine = nullptr;
};


#pragma once

interface IMeshObject;
class CGameObject : public IUnknown
{
	COM_FUNC
public:
	CGameObject() = default;
	~CGameObject() = default;

public:
	HRESULT Initialize();
	void Tick(FLOAT fDeltaTime);
	void Late_Tick(FLOAT fDeltaTime);
	void Render();

private:
	IMeshObject* m_pMeshObj = nullptr;
};


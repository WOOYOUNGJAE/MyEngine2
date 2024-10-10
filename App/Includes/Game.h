#pragma once

interface IRenderer;
class CGameObject;

class CGame : public IUnknown
{
	COM_FUNC
public:
	CGame() = default;
	~CGame();
public:
	HRESULT Initialize(std::string& strTitle);
	void Run();

public:
	IRenderer* m_pRenderer = nullptr;
private:
	std::list<CGameObject*> m_GameObjList;
};


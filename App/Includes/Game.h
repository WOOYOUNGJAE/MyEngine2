#pragma once

class CEngine_Core;
class CGameObject;

class CGame : public IUnknown
{
	COM_BASE
public:
	CGame() = default;
	~CGame();
public:
	HRESULT Initialize(std::string& strTitle);
	void Run();

public:
	CEngine_Core* m_pEngine = nullptr;
private:
};


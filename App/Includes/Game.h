#pragma once

struct IEngine;
class CGame : public IUnknown
{
	COM_FUNC
public:
	CGame() = default;
	~CGame();
public:
	HRESULT Initialize(std::string& strTitle);
	void Run();

private:
	IEngine* m_pEngine = nullptr;
};


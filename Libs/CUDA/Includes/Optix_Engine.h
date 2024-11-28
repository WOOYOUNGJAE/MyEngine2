#pragma once

class COptix_Engine : public IUnknown
{
	COM_BASE
public:
	COptix_Engine() = delete;
	COptix_Engine(UINT uiWidth, UINT uiHeight);
	~COptix_Engine();
};


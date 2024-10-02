#pragma once
#include "Engine_Common/EngineConfig.h"

interface ENGINECOMMON_DLL IMeshObject : public IUnknown
{
};

interface ENGINECOMMON_DLL IEngine : public IUnknown
{
	class OpenGL {};
	class DirectX12 {};

	virtual HRESULT Initialize(void*) = 0;
	virtual INT Engine_Tick(FLOAT fDeltaTime = 0.2f) = 0;
	// Render Func
	virtual void BeginRender() = 0;
	virtual void MainRender() = 0;
	virtual void EndRender() = 0;
};
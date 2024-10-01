#pragma once
#include "Engine_Common/EngineConfig.h"

class ENGINECOMMON_DLL IEngine
{
public:
	class OpenGL {};
	class DirectX12 {};

public:
	IEngine();
	virtual ~IEngine() = default;
public:
	virtual INT Engine_Tick(BOOL bShouldClose, FLOAT fDeltaTime = 0.2f) = 0;
};


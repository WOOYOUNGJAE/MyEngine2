#pragma once
#include "Engine_Common/EngineConfig.h"

class ENGINECOMMON_DLL IRenderer
{
public:
	class OpenGL {};
	class DirectX12 {};

public:
	IRenderer();
	virtual ~IRenderer() = default;
};


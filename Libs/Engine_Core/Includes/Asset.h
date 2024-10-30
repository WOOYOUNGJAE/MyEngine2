#pragma once
#include "EngineConfig.h"

class ENGINECORE_DLL CAsset abstract : public IUnknown
{
	COM_BASE
public:
	CAsset() = default;
	~CAsset() = default;

public:
	const wchar_t* m_wszPath;
};


#pragma once
#include "AssetLoaderConfig.h"

class CEngine_Core;
class ASSETLOADER_DLL CAsset_Loader : public IUnknown
{
	COM_BASE
public:
	CAsset_Loader() = default;
	~CAsset_Loader() = default;

private:// Pointer
	CEngine_Core* m_pEngine_Core = nullptr;
};


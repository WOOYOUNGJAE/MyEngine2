#pragma once
#include "AssetLoaderConfig.h"

class CEngine_Core;
class ASSETLOADER_DLL CAsset_Loader : public IUnknown
{
	COM_BASE
public:
	CAsset_Loader() = delete;
	CAsset_Loader(CEngine_Core* pEngine_Core);
	~CAsset_Loader() = default;
public:
	/**
	 * @note Reference to SIBR - 3DGS
	 */
	HRESULT Load_Ply(const wchar_t* wszPath);

private:// Pointer
	CEngine_Core* m_pEngine_Core = nullptr;
private:
};
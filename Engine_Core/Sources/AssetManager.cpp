#include "pch.h"
#include "AssetManager.h"
#include "Asset.h"
#include "Asset_ply.h"

IMPL_COM_FUNC(CAssetManager)

CAssetManager::~CAssetManager()
{
	for (auto& iterPair : m_mapPlys)
	{
		RELEASE_INSTANCE(iterPair.second);
	}
}

void CAssetManager::Add_Ply(const wchar_t* wszPath, CAsset* pAssetInstance)
{
	if (pAssetInstance == nullptr)
	{
		__debugbreak();
	}

	m_mapPlys.emplace(std::wstring(wszPath), pAssetInstance);
}

CAsset_ply* CAssetManager::Get_Ply(const wchar_t* wszPath)
{
	CAsset_ply* pOutInstance = nullptr;

	auto iterator = m_mapPlys.find(std::wstring(wszPath));

	// Failed to Find
	if (iterator == m_mapPlys.end())
	{
		return pOutInstance;
	}

	pOutInstance = dynamic_cast<CAsset_ply*>(iterator->second);

	return pOutInstance;
}

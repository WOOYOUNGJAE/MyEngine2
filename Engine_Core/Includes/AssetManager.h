#pragma once

class CAsset;
class CAsset_ply;
class CAssetManager : public IUnknown
{
	COM_BASE
public:
	CAssetManager() = default;
	~CAssetManager();
public:
	void Add_Ply(const wchar_t* wszPath, CAsset* pAssetInstance);
	CAsset_ply* Get_Ply(const wchar_t* wszPath);
	std::map<std::wstring, CAsset_ply*>& Get_PlyMap() { return m_mapPlys; }

private:
	std::map<std::wstring, CAsset_ply*> m_mapPlys;
};


#pragma once
#include "Asset.h"

constexpr int iFixedDimension = 3;

template<int D>
struct SHs
{
	float shs[(D + 1) * (D + 1) * 3];
};

class ENGINECORE_DLL CAsset_ply : public CAsset
{
public:
	CAsset_ply() = default;
	~CAsset_ply() override;
public:

public:
	std::vector<XMFLOAT3> m_vecPos;
	std::vector<XMFLOAT4> m_vecRot;
	std::vector<XMFLOAT3> m_vecScale;
	std::vector<FLOAT> m_vecOpacity;
	std::vector<SHs<iFixedDimension>> m_vecShs;
	std::vector<XMFLOAT3> m_vecNormal;
	XMFLOAT3 m_vMin{};
	XMFLOAT3 m_vMax{};
	UINT m_iNumPoints = 0;
};


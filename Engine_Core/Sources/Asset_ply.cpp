#include "pch.h"
#include "Asset_ply.h"

CAsset_ply::~CAsset_ply()
{
	m_vecPos.clear();
	m_vecRot.clear();
	m_vecScale.clear();
	m_vecOpacity.clear();
	m_vecShs.clear();
	m_vecNormal.clear();
}

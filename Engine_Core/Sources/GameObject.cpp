#include "pch.h"
#include "GameObject.h"
#include "Engine_Core.h"
#include "Transform.h"
IMPL_COM_FUNC(CGameObject)

void CGameObject::Late_Tick(FLOAT fDeltaTime)
{
	if (m_pTransform.m_bTransformDirty == true)
	{
		m_pTransform.Update_Transform();
	}
}

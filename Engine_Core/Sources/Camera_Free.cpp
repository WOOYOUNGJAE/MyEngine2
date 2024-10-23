#include "pch.h"
#include "Camera_Free.h"
#include "InputManager.h"

void CCamera_Free::Tick(FLOAT fDeltaTime)
{
	FLOAT fCurMoveSpeed = m_fMoveSpeed;
	FLOAT fRotRotSpeed = m_fRotSpeed;
	if (g_Input->Key_Pressing(VK_LSHIFT))
	{
		fCurMoveSpeed = m_fMoveSpeed * 3;
		fRotRotSpeed = m_fRotSpeed * 2;
	}

	if (g_Input->Key_Pressing(VK_ESCAPE));

	if (g_Input->Key_Pressing('W'))
	{
		m_pTransform.Set_Position(m_pTransform.m_vPosition + m_pTransform.Look() * fCurMoveSpeed * fDeltaTime);
	}
	if (g_Input->Key_Pressing('D'))
	{
		m_pTransform.Set_Position(m_pTransform.m_vPosition + m_pTransform.Right() * fCurMoveSpeed * fDeltaTime);
	}
	if (g_Input->Key_Pressing('S'))
	{
		m_pTransform.Set_Position(m_pTransform.m_vPosition + m_pTransform.Look() * -fCurMoveSpeed * fDeltaTime);
	}
	if (g_Input->Key_Pressing('A'))
	{
		m_pTransform.Set_Position(m_pTransform.m_vPosition + m_pTransform.Right() * -fCurMoveSpeed * fDeltaTime);
	}
	if (g_Input->Key_Pressing('Q'))
	{
		m_pTransform.Set_Position(m_pTransform.m_vPosition + m_pTransform.Up() * fCurMoveSpeed * fDeltaTime);
	}
	if (g_Input->Key_Pressing('E'))
	{
		m_pTransform.Set_Position(m_pTransform.m_vPosition + m_pTransform.Up() * -fCurMoveSpeed * fDeltaTime);
	}

	//if (g_Input->Key_Pressing(VK_RBUTTON))
	//{
	//	const Vector2& vChangedDir = g_Input->Get_MouseDirPrevToCur();

	//	// 먼저 절대적인 y축을 기준으로 회전 해야 함
	//	m_pTransformCom->Rotate(Vector3::Up, vChangedDir.x * fRotRotSpeed * fDeltaTime);
	//	m_pTransformCom->Rotate(m_pTransformCom->WorldMatrix().Right(), vChangedDir.y * fRotRotSpeed * fDeltaTime);

	//}



	//if (g_Input->Key_Down('X')) // 카메라 회전 되돌리기
	//{
	//	m_pTransformCom->Set_Look(Vector3(0.f, 0.f, 1.f));
	//}
}

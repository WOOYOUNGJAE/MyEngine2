#include "pch.h"
#include "Camera_Free.h"
#include "InputManager.h"


static Vector3 vStartPos = Vector3(0, 0, -2);
static Matrix matStartRotation;
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
		m_pTransform.Set_Position(m_pTransform.m_vPosition + m_pTransform.Up() * -fCurMoveSpeed * fDeltaTime);
	}
	if (g_Input->Key_Pressing('E'))
	{
		m_pTransform.Set_Position(m_pTransform.m_vPosition + m_pTransform.Up() * fCurMoveSpeed * fDeltaTime);
	}

	if (g_Input->Key_Pressing(VK_RBUTTON))
	{
		const Vector2& vChangedDir = g_Input->Get_MouseDirPrevToCur();

		Quaternion rotationX = Quaternion::CreateFromAxisAngle(Vector3::Up, vChangedDir.x * m_fRotSpeed * fDeltaTime);
		m_pTransform.Multiple_Rotation(Matrix::CreateFromQuaternion(rotationX));
		Quaternion rotationY = Quaternion::CreateFromAxisAngle(m_pTransform.m_matRotation.Right(), vChangedDir.y * m_fRotSpeed * fDeltaTime);
		m_pTransform.Multiple_Rotation(Matrix::CreateFromQuaternion(rotationY));
		
	}
	static float fAccAngle = 0.f;
	fAccAngle = fDeltaTime * 0.07f;
	Quaternion rot = Quaternion::CreateFromAxisAngle(Vector3::Up, fAccAngle);
	//Quaternion rot = Quaternion::CreateFromAxisAngle(Vector3::Right, fAccAngle);
	//m_pTransform.Multiple_Rotation(Matrix::CreateFromQuaternion(rot));


	if (g_Input->Key_Down('X')) // 카메라 원위치
	{
		m_pTransform.Set_Position(vStartPos);
		m_pTransform.Set_Rotation(matStartRotation);
	}
}

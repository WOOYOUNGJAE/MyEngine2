#include "pch.h"
#include "Camera.h"
#include "GameObject.h"

void CCamera::Initialize(CEngine_Core* pEngine)
{
}

void CCamera::Tick(FLOAT fDeltaTime)
{
}

void CCamera::Late_Tick(FLOAT fDeltaTime)
{
	CGameObject::Late_Tick(fDeltaTime);
}

Matrix CCamera::ViewMatrix()
{
	return m_pTransform.m_matWorld.Invert();
}

Matrix CCamera::ProjMatrix()
{
	return Matrix(XMMatrixPerspectiveFovLH(m_CamDesc.fFovY, m_CamDesc.fAspectRatio, m_CamDesc.fNear, m_CamDesc.fFar));
}

Matrix CCamera::ViewProjection()
{
	Matrix matView = m_pTransform.m_matWorld.Invert();
	Matrix matProj = Matrix(XMMatrixPerspectiveFovLH(m_CamDesc.fFovY, m_CamDesc.fAspectRatio, m_CamDesc.fNear, m_CamDesc.fFar));

	return matView * matProj;
}

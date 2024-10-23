#include "pch.h"
#include "Transform.h"

void CTransform::Set_Position(FLOAT x, FLOAT y, FLOAT z)
{
	m_vPosition.x = x;	m_vPosition.y = y;	m_vPosition.z = z;
	m_bTransformDirty = true;
}

void CTransform::Set_Position(const Vector3& vNewPos)
{
    m_vPosition = vNewPos;
	m_bTransformDirty = true;
}

void CTransform::Set_Rotation(UINT axis, FLOAT fAngle)
{
    switch (axis)
    {
    case 0: // X
        m_matRotation = Matrix::CreateRotationX(fAngle);
        break;
    case 1: // Y
        m_matRotation = Matrix::CreateRotationY(fAngle);
        break;
    case 2: // Z
        m_matRotation = Matrix::CreateRotationZ(fAngle);
        break;
    default:
        break;
    }
    m_bTransformDirty = true;
}

void CTransform::Update_Transform()
{
    Matrix matTranslation = Matrix::CreateTranslation(m_vPosition);
    Matrix matScale = Matrix::CreateScale(m_vScale);

    m_matWorld = matScale * m_matRotation * matTranslation;
    m_bTransformDirty = false;
}

Vector3 CTransform::Look()
{
	return -m_matRotation.Forward(); // Forward() is towarding to Screen
}

Vector3 CTransform::Get_Look_GL()
{
	return m_matRotation.Forward(); // Forward() is towarding to Screen
}

Matrix CTransform::WorldMatrix_GL()
{
	Matrix matWorld_GL = m_matWorld;
	matWorld_GL._31 *= -1;
	matWorld_GL._32 *= -1;
	matWorld_GL._33 *= -1;
	matWorld_GL._34 *= -1;

	return matWorld_GL;
}

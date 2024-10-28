#pragma once
#include "EngineConfig.h"
#include "SimpleMath.h"

/**
 * @brief
 * Works with DirectX standards.
 * Use the GL getter for GL, but Still Row Major
 */
class ENGINECORE_DLL CTransform
{
public:
	void Set_Position(FLOAT x, FLOAT y, FLOAT z);
	void Set_Position(const Vector3& vNewPos);
	void Set_Rotation(const Matrix& matRot) { m_matRotation = matRot; m_bTransformDirty = true; }
	void Set_Rotation(UINT axis, FLOAT fAngle);
	void Multiple_Rotation(const Matrix& matRot);
	void Update_Transform();
	Vector3 Right() { return m_matRotation.Right(); }
	Vector3 Up() { return m_matRotation.Up(); }
	Vector3 Look(); // Get Look(Forward)
	Vector3 Forward() { return Look(); }; // Get Look(Forward)
	Vector3 Get_Look_GL();
	Vector3 Position() { return m_vPosition; }
	Matrix WorldMatrix() { return m_matWorld; }
	Matrix WorldMatrix_GL();

public:
	bool m_bTransformDirty = false; // Update Trasform If True
	Vector3 m_vPosition = Vector3::Zero;
	Vector3 m_vScale = Vector3::One;
	Matrix m_matWorld;
	Matrix m_matRotation;
};
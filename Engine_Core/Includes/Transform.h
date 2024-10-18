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
	void Set_Rotation(UINT axis, FLOAT fAngle);
	void Update_Transform();
	Vector3 Get_Look_DX(); // Get Look(Forward)
	Vector3 Get_Look_GL();
	Matrix WorldMatrix() { return m_matWorld; }
	Matrix WorldMatrix_GL();

public:
	bool m_bTransformDirty = false; // Update Trasform If True
	Vector3 m_vPosition = Vector3::Zero;
	Vector3 m_vScale = Vector3::One;
	Matrix m_matWorld;
	Matrix m_matRotation;
};
#pragma once
#include "Camera.h"

class ENGINECORE_DLL CCamera_Free : public CCamera
{
public:
	CCamera_Free()
	{
		m_fMoveSpeed = 0.1f;
		m_fRotSpeed = 0.01f;
	}
	~CCamera_Free() override = default;
public:
	void Tick(FLOAT fDeltaTime) override;
};


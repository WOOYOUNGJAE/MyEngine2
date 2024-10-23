#pragma once
#include "Camera.h"

class ENGINECORE_DLL CCamera_Free : public CCamera
{
public:
	CCamera_Free()
	{
		m_fMoveSpeed = 1.f;
		m_fRotSpeed = 0.5f;
	}
	~CCamera_Free() override = default;
public:
	void Tick(FLOAT fDeltaTime) override;
};


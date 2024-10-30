#pragma once
#include "GameObject.h"
#include "Common/Includes/RendererInterface.h"

class ENGINECORE_DLL CCamera : public CGameObject
{
public:
	CCamera() {}
	~CCamera() override = default;

public:
	void Initialize(CEngine_Core* pEngine) override;
	void Tick(FLOAT fDeltaTime) override;
	void Late_Tick(FLOAT fDeltaTime) override;
	void Render() override{}; // Do Nothing
public:
	Matrix ViewMatrix();
	Matrix ProjMatrix();
	Matrix ViewProjection(); // View * Projection

public:
	CAMERA_DESC m_CamDesc{};
protected:
	FLOAT m_fMoveSpeed = 1.f;
	FLOAT m_fRotSpeed = 1.f;
};


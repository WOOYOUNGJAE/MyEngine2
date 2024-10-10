#pragma once
#include "Engine_Core/Includes/GameObject.h"
class CTestGameObj : public CGameObject
{
public:
	CTestGameObj() = default;
	virtual ~CTestGameObj();
	
public:
	void Initialize(CEngine_Core* pEngine) override;
	void Tick(FLOAT fDeltaTime) override;
	void Late_Tick(FLOAT fDeltaTime) override;
	void Render() override;

};


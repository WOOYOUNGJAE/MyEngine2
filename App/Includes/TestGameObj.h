#pragma once
#include "GameObject.h"
class CTestGameObj : public CGameObject
{
	COM_FUNC
public:
	CTestGameObj() = default;
	virtual ~CTestGameObj();

public:
	void Initialize(CGame* pGame) override;
	void Tick(FLOAT fDeltaTime) override;
	void Late_Tick(FLOAT fDeltaTime) override;
	void Render() override;

};


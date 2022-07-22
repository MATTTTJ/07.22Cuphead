#pragma once
#include "Effect.h"
class CMonster_Dead_Effect :
	public CEffect
{
public:
	CMonster_Dead_Effect();
	virtual ~CMonster_Dead_Effect();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};


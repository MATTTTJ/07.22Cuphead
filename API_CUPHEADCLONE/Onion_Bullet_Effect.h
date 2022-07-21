#pragma once
#include "Effect.h"
class COnion_Bullet_Effect :
	public CEffect
{
public:
	COnion_Bullet_Effect();
	virtual ~COnion_Bullet_Effect();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};


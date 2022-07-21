#pragma once
#include "Effect.h"
class CFlower_Bullet_Dead :
	public CEffect
{
public:
	CFlower_Bullet_Dead();
	virtual ~CFlower_Bullet_Dead();
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};


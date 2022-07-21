#pragma once
#include "Effect.h"
class CBullet_Death :
	public CEffect
{
public:
	CBullet_Death();
	virtual ~CBullet_Death();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};


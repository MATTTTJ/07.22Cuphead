#pragma once
#include "Effect.h"
class CBullet_Effect :
	public CEffect
{
public:
	CBullet_Effect();
	virtual ~CBullet_Effect();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

};


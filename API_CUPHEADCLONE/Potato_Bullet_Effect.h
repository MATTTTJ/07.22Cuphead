#pragma once
#include "Effect.h"
class CPotato_Bullet_Effect :
	public CEffect
{
public:
	CPotato_Bullet_Effect();
	virtual ~CPotato_Bullet_Effect();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};


#pragma once
#include "Effect.h"
class CParry_Splash_Effect :
	public CEffect
{
public:
	CParry_Splash_Effect();
	virtual ~CParry_Splash_Effect();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

};


#pragma once
#include "Effect.h"
class CTears_Splash_Effect :
	public CEffect
{
public:
	CTears_Splash_Effect();
	virtual ~CTears_Splash_Effect();


	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

};


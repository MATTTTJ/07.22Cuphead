#pragma once
#include "Effect.h"
class CParry_Effect :
	public CEffect
{
public:
	CParry_Effect();
	virtual ~CParry_Effect();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

};


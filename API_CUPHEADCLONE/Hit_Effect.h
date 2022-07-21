#pragma once
#include "Effect.h"
class CHit_Effect :
	public CEffect
{
public:
	CHit_Effect();
	virtual ~CHit_Effect();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};


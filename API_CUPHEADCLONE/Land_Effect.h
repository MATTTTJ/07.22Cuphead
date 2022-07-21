#pragma once
#include "Effect.h"
class CLand_Effect :
	public CEffect
{
public:
	CLand_Effect();
	virtual ~CLand_Effect();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};


#pragma once
#include "Effect.h"
class CCloud_Dead :
	public CEffect
{
public:
	CCloud_Dead();
	virtual ~CCloud_Dead();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};


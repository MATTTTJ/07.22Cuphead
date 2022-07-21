#pragma once
#include "Effect.h"
class CPlayer_Dust :
	public CEffect
{
public:
	CPlayer_Dust();
	virtual ~CPlayer_Dust();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};


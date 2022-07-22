#pragma once
#include "Effect.h"
class CCloud_Birth :
	public CEffect
{
public:
	CCloud_Birth();
	virtual ~CCloud_Birth();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};


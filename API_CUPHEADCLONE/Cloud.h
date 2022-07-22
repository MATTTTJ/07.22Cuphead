#pragma once
#include "Monster.h"
class CCloud :
	public CObj
{
public:
	CCloud();
	virtual ~CCloud();


	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};


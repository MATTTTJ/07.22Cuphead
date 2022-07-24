#pragma once
#include "Monster.h"
class CStar :
	public CMonster
{
public:
	CStar();
	virtual ~CStar();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collision_Event(CObj* _OtherObj, float fColX, float fColY) override;


private:
	DWORD		m_dwChaserTime = GetTickCount();
};


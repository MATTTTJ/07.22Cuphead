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

	float fCenterX;
	float fCenterY;
	float m_fRotAngle = 0.f;
	float m_fRotSpeed = 30.f;
		
	DWORD		m_dwChaserTime = GetTickCount();

	DWORD		m_dwLiveTime = GetTickCount();
};


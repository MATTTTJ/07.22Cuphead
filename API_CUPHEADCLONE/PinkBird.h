#pragma once
#include "Monster.h"
class CPinkBird :
	public CMonster
{
public:
	CPinkBird();
	virtual ~CPinkBird();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collision_Event(CObj* _OtherObj, float fColX, float fColY) override;


private:
	float		m_fHp;
	float		m_fMaxHp;
	DWORD		m_dwTimer;
};


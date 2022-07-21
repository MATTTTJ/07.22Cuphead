#pragma once
#include "Monster.h"
class CDotori :
	public CMonster
{
	enum DOTORISTATE { WALK, ATTACK, MOTION_END };


public:
	CDotori();
	virtual ~CDotori();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collision_Event(CObj* _OtherObj, float fColX, float fColY) override;
	void		Drop_Dotori(void);
private:
	void		Motion_Change(void);

	bool		m_bIsDetected = false;
	float		m_fHp;
	float		m_fMaxHp;

	float		m_fStartX = 0.f;

	DWORD		m_dwTimer;

	DOTORISTATE		m_eCurState;
	DOTORISTATE		m_ePreState;
};


#pragma once
#include "Monster.h"
class CFlyingMan :
	public CMonster
{
	enum FLYINGMANSTATE { INTRO_AIR, LAND, WALK, MOTION_END };

public:
	CFlyingMan();
	virtual ~CFlyingMan();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collision_Event(CObj* _OtherObj, float fColX, float fColY) override;
	void		Motion_Change(void);

private:
	float		m_fHp;
	float		m_fMaxHp;
	bool		m_bLineCol = false;

	float		m_fMaxAbsJumpSpeed = 25.f;
	float		m_fInitJumpSpeed = 24.f;
	float		m_fCurJumpSpeed = 0.f;
	float		m_fFootY = 0.f;

	OBJECTSTATE			m_eState;
	FLYINGMANSTATE		m_eCurState;
	FLYINGMANSTATE		m_ePreState;
	DWORD				m_dwTimer;
};


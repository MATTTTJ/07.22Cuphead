#pragma once
#include "Monster.h"
class COnion : public CMonster
{
	enum ONIONSTATE { INTRO_EARTH,INTRO, IDLE,BEFORE_ATTACK, ATTACK,CHANGETOATTACK, HIT, DEAD, BMOTION_END };

public:
	COnion();
	virtual ~COnion();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collision_Event(CObj* _OtherObj, float fColX, float fColY) override;
	virtual void Update_Controller();
private:
	void		Motion_Change(void);
	void		Onion_Intro_Earth(void);
	void		Onion_Intro(void);
	void		Onion_Attack_End(void);
	void		Onion_Idle_End(void);
	float		m_fHp;
	float		m_fMaxHp;



	

	bool			m_bIsFirstHit = false;
	bool			m_bIsHit = false;
	bool			m_bShootState = false;
	
	DWORD			m_dwTimer;
	bool			m_bShoot_Start = false;

	ONIONSTATE			m_ePreState;
	ONIONSTATE			m_eCurState;

	list<CObj*>*		m_pBullet = nullptr;
};


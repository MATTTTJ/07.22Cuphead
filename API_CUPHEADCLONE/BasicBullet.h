#pragma once
#include "Bullet.h"
class CBasicBullet :
	public CBullet
{
	enum BULLETSTATE { BIRTH,DEAD,ATTACK, SHOOTEND};


public:
	CBasicBullet();
	virtual ~CBasicBullet();
	void	SetPlayer(CObj* pobj) { m_pPlayer = pobj; }
	virtual float Get_Damage() const { return m_HInfo.m_fDamage; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual	void Collision_Event(CObj* _OtherObj, float _fColX, float _fColY) override;
	void		 Motion_Change(void);

	void		Bullet_Intro(void);

private:
	CObj* m_pPlayer;
	BULLETSTATE	 m_eCurState;
	BULLETSTATE	 m_ePreState;

	bool	m_bFirstIntro = false;
};


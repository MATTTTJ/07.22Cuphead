#pragma once
#include "Monster.h"

typedef list<CObj*>		BULLETLIST;

class CPotato :public CMonster
	
{
	enum POTATOSTATE { INTRO_EARTH, INTRO,IDLE, ATTACK, HIT, DEAD, BMOTION_END };

public:
	CPotato();
	virtual ~CPotato();

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
	void		Potato_Intro_Earth(void);
	void		Potato_Intro(void);

	float		m_fHp;
	float		m_fMaxHp;

	

	
	
	bool			m_bShootState = false;
	DWORD			m_dwTimer;
	


	POTATOSTATE			m_ePreState;
	POTATOSTATE			m_eCurState;
	list<CObj*>*		m_pBullet = nullptr;
};


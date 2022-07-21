#pragma once
#include "Monster.h"
class CTaurus :
	public CMonster
{
	enum TAURUSSTATE { INTRO_STAR, INTRO, IDLE, ATTACK, DEAD, MOTION_END };

public:
	CTaurus();
	virtual ~CTaurus();

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
	void		Taurus_Intro_Star(void);
	void		Taurus_Intro(void);

	float		m_fHp;
	float		m_fMaxHp;




	TAURUSSTATE		m_eCurState;
	TAURUSSTATE		m_ePreState;

	bool			m_bShootState = false;
	DWORD			m_dwTimer;


};


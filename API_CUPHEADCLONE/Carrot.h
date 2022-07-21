#pragma once
#include "Monster.h"
typedef list<CObj*>		BULLETLIST;

class CCarrot :public CMonster
{
	enum CARROTSTATE { INTRO_EARTH, INTRO, IDLE, ATTACK,CHANGETOATTACK,BEAM, HIT, DEAD, BMOTION_END };
public:
	CCarrot();
	virtual ~CCarrot();

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
	void		Carrot_Intro_Earth(void);
	void		Carrot_Intro(void);

	float		m_fHp;
	float		m_fMaxHp;



	int				m_iBeamCnt = 6;
	int				m_iBeamMaxCnt = 5;
	
	bool			m_bBeamState = false;
	bool			m_bIsBeamStart = false;
	bool			m_bShootState = false;
	bool			m_bBeam_Start = false;
	bool			m_bBeam_Attack = false;

	DWORD			m_dwTimer;

	CObjTimer		BeamTimer;
	CObjTimer		BeamCoolTimer;
	CObjTimer		BeamAttackTimer;

	CObjTimer		BeamStateTimer;
	CObjTimer		BeamStateCoolTimer; 

	CARROTSTATE			m_ePreState;
	CARROTSTATE			m_eCurState;
	list<CObj*>*		m_pBullet = nullptr;
};



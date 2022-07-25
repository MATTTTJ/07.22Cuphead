#pragma once
#include "Monster.h"
class CSagittarius :
	public CMonster
{
	enum SAGITTARIUSSTATE { INTRO_STAR, INTRO, IDLE, ATTACK, DEAD, MOTION_END };


public:
	CSagittarius();
	virtual ~CSagittarius();


public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collision_Event(CObj* _OtherObj, float fColX, float fColY) override;
	virtual void Update_Controller();
	void		 Check_PhaseTwo(void);
private:
	void		Motion_Change(void);
	void		Sagittarius_Intro_Star(void);
	void		Sagittarius_Intro(void);

	float		m_fHp;
	float		m_fMaxHp;

	bool		m_bPhaseOne = false;
	bool		m_bPhaseTwo = false;
	bool		m_bPhaseThree = false;

	bool		m_bFisrtTime = false;

	int			m_iStarCnt = 0;
	int			m_iStarMaxCnt = 0;


	SAGITTARIUSSTATE		m_eCurState;
	SAGITTARIUSSTATE		m_ePreState;

	bool			m_bShootState = false;
	DWORD			m_dwTimer;
	DWORD			m_dwDustTime = GetTickCount();
	DWORD			m_dwStarCoolTime = GetTickCount();

};


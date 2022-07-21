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

private:
	void		Motion_Change(void);
	void		Sagittarius_Intro_Star(void);
	void		Sagittarius_Intro(void);

	float		m_fHp;
	float		m_fMaxHp;




	SAGITTARIUSSTATE		m_eCurState;
	SAGITTARIUSSTATE		m_ePreState;

	bool			m_bShootState = false;
	DWORD			m_dwTimer;


};


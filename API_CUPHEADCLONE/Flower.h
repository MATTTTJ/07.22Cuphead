#pragma once
#include "Monster.h"
class CFlower :
	public CMonster
{

	enum FLOWERSTATE { IDLE, ATTACK, MOTION_END };


public:
	CFlower();
	virtual ~CFlower();
	
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
	bool			m_bShootState = false;
	float		m_fHp;
	float		m_fMaxHp;
	DWORD		m_dwTimer;

	FLOWERSTATE		m_eCurState;
	FLOWERSTATE		m_ePreState;
};


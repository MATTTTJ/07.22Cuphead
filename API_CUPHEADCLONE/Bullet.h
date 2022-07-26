#pragma once
#include "Obj.h"
class CBullet :
	public CObj
{
	

public:
	CBullet();
	virtual ~CBullet();
	void	SetPlayer(CObj* pobj) { m_pPlayer = pobj; }
	virtual float Get_Damage() const { return m_HInfo.m_fDamage; }
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual	void Collision_Event(CObj* _OtherObj, float _fColX, float _fColY) override;
	


private:
	CObj* m_pPlayer;


	float m_fCurJumpSpeed = 0.f;
	float m_fMaxAbsJumpSpeed = 16.f;
	float m_fInitJumpSpeed = 15.f;

	//Bullet Bounce
	int  m_iJumpCnt = 0;
	int  m_iJumpMaxCnt = 3;
	bool m_bJump = true;
	//~Bullet Bounce
protected:

	bool	m_bFirstRender;

};


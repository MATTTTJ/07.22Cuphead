#pragma once
#include "Bullet.h"
class CFlower_Bullet :
	public CBullet
{
public:
	CFlower_Bullet();
	virtual ~CFlower_Bullet();

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
	float m_fMaxAbsJumpSpeed = 25.f;
	float m_fInitJumpSpeed = 24.f;

	int  m_iJumpCnt = 0;
	int  m_iJumpMaxCnt = 3;
	bool m_bJump = true;
};


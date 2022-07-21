#pragma once
#include "Bullet.h"
class CCarrot_Beam :
	public CBullet
{
public:
	CCarrot_Beam();
	virtual ~CCarrot_Beam();

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
	bool	m_bIsSplash = false;

	float	fW;
	float	fH;

	float m_fDX;
	float m_fDY;
};


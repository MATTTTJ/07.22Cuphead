#pragma once
#include "Obj.h"

typedef list<CObj*>		BULLETLIST;

class CPlayer :	public CObj
{
	enum STATE { CROUCH,IDLE,DASH, RUN,JUMP, ATTACK,ATTACK_UP,ATTACK_DIR,RUNNING_ATTACK_HOR,RUNNING_ATTACK_DIR,PARRY, HIT, DEAD, MOTION_END };
	
public:
	CPlayer();
	virtual ~CPlayer();
	float		g_fSound = 1.f;
public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual	void Collision_Event(CObj* _OtherObj, float _fColX, float _fColY) override;
private:
	void		Key_Input(void);
	void		Jumping(void);
	void		Offset(void);
	void		Motion_Change(void);
	void		Dash(void);
	void		Shoot_Hor(void);
	void		Shoot_DIR(void);
	void		Run_Shoot_Hor(void);
	void		Parry(void);
	void		Ground_Check(void);
	template<typename T>
	CObj*		Create_Bullet(float _fX, float _fY, DIR eDir = DIR_END);
	void		Update_Parry(void);
private:
	//Jump
	bool		m_bJump = false;
	float		m_fMaxAbsJumpSpeed = 25.f;
	float		m_fInitJumpSpeed = 24.f;
	float		m_fCurJumpSpeed = 0.f;
	bool		m_bLineCol = false;
	float		m_fFootY = 0.f;
	float		m_fPreFootY = 999999.f;
	int			m_iJumpCount = 0;
	float		m_fJumpPower = 0.f;
	float		m_fJumpTime = 0.f;
	//~Jump
	bool m_bGround = false;
	DWORD		m_dwDustTime;

	//Hit
	bool		m_bIsHit = false;
	DWORD		m_dwHitTime;
	//~Hit

	//Dash
	bool		m_bDash = false;
	//~Dash

	//Shoot
	bool		m_bShoot = false; 
	bool		m_bDirShoot = false;
	bool		m_bShoot_Dir = false;
	bool		m_bRun_Shoot = false;
	bool		m_bBulletCnt = false;
	bool		m_bBulletDir = false;
	//~Shoot

	//Parry
	bool		m_bIsParry = false;
	bool		m_bParryShake = false;
	DWORD		m_dwParry = GetTickCount();
	float		m_fParryCoolTIme = 0.3f;
	DWORD		m_dwParryWaitTime;
	//~Parry

	//Shake
	bool m_bScrollShake = true;
	int m_iShakeCnt = 6;
	int m_iShakeMaxCnt = 6;
	DWORD m_dwShaketimer;
	//~Shake


	

	float		m_fDashSpeed = 0.f;

	//PLAYERINFO		m_tStat;
	OBJECTSTATE		m_eState;
	STATE			m_ePreState;
	STATE			m_eCurState;
	LOOK			m_eLookState;
	DWORD			m_dwDash = GetTickCount();
	DWORD			m_dwAttack = GetTickCount();


	float			m_fDashCoolTIme = 0.3f;
	DWORD			m_dwDashWaitTime;





	list<CObj*>*		m_pBullet = nullptr;

protected:
	float		m_iSpecial_Gauge;

};


#pragma once
#include "Obj.h"
#include "ObjTimer.h"

class CMonster : public CObj
{
	enum MSTATE { IDLE, ATTACK, HIT, DEAD, MSTAT_END};


public:
	CMonster();
	virtual ~CMonster();
	virtual float Get_Damage() const { return m_tInfo.m_fDamage; }
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collision_Event(CObj * _OtherObj, float _fColX, float _fColY) override;
	virtual void Update_Controller();
	virtual void Monster_Input(MONSTER_INPUT _eInput);
	virtual bool PlayerDetect(float _fRange);
protected:
	float	 m_fHp;
	float	 m_fMaxHp;
	float	 m_fDetectRange;
	bool	 m_bDetected = false;
	bool			m_bIsAttackEnd = false;
	bool			m_bIsIdleEnd = false;
	bool			m_bShoot_Start = false;
	bool			m_bIsIntro_First = false;
	bool			m_bIsIntro_Second = false;
	bool			m_bIsReadyAttack = false;
	int				m_iShootFrameCnt;
	int				m_iShootFrameMaxCnt;
	int				m_iShootCnt;
	int				m_iShootMaxCnt;



	CObjTimer		ShootCoolTimer;
	CObjTimer		ShootTimer;

	CObjTimer		ShootStateTimer;
	CObjTimer		ShootStateCoolTimer;
	CObjTimer		m_AttackTimer;

};


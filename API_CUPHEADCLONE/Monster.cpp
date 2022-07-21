#include "stdafx.h"
#include "Monster.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "LineMgr.h"



CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
}

int CMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
}

void CMonster::Render(HDC hDC)
{
}

void CMonster::Release(void)
{

}

void CMonster::Collision_Event(CObj * _OtherObj, float _fColX, float _fColY)
{
}

void CMonster::Update_Controller()
{
	/*if (!PlayerDetect()) return;

	if (m_MoveTimer.Check())
	{
		switch (m_Move)
		{
		case MON_LEFT:
			m_Move = MON_RIGHT;
			break;
		case MON_RIGHT:
			m_Move = MON_LEFT;
			break;
		}
	}

	if (m_JumpTimer.Check())
	{
		Monster_Input(MON_JUMP);
	}

	if (m_AttackTimer.Check())
	{
		Monster_Input(MON_ATTACK);
	}

	Monster_Input(m_Move);*/
}

void CMonster::Monster_Input(MONSTER_INPUT _eInput)
{
}

bool CMonster::PlayerDetect(float _fRange)
{
		CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();

		float fDiffX = pPlayer->Get_Info().fX - m_tInfo.fX;
		float fDiffY = pPlayer->Get_Info().fY - m_tInfo.fY;

		float fDistance = sqrtf(fDiffX * fDiffX + fDiffY * fDiffY);

		return fDistance <= _fRange;
}

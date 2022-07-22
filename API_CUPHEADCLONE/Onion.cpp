#include "stdafx.h"
#include "Onion.h"
#include "ObjMgr.h"
#include "Bullet_Effect.h"
#include "EffectMgr.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Onion_Bullet.h"
#include "Onion_Bullet_Effect.h"
#include "Carrot.h"
#include"Onion_Parry_Bullet.h"
COnion::COnion()
	:m_eCurState(INTRO_EARTH), m_ePreState(INTRO_EARTH)
{
}


COnion::~COnion()
{
	Release();
}

void COnion::Initialize(void)
{
	m_tInfo = { 950.f, 450.f, 557.f, 461.f };
	m_HInfo = { 950.f, 450.f, 370.f, 450.f };

	m_fHp = 3.f;

	//When the Potato Bullet Create
	ShootTimer.InitLoop(5.1f);
	//The Potato Bullet Distance 
	ShootCoolTimer.InitLoop(0.3f);

	ShootStateTimer.InitLoop(5.1f);
	ShootStateCoolTimer.InitLoop(1.2f);

	//이미지 마저 수정하기
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Onion/Onion_Intro_Earth.bmp", L"Onion_Intro_Earth");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Onion/Onion_Intro.bmp", L"Onion_Intro");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Onion/Onion_Idle.bmp", L"Onion_Idle"); 
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Onion/Onion_BeforeAttack.bmp", L"Onion_BeforeAttack"); 
														   
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Onion/Onion_Attack.bmp", L"Onion_Attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Onion/Onion_ChangeToAttack.bmp", L"Onion_ChangeToAttack"); 
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Onion/Onion_Death.bmp", L"Onion_Death"); 

	m_pFrameKey = L"Onion_Intro_Earth";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 17;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_dwTimer = GetTickCount();

	m_bIsIntro_First = true;
	m_bIsFirstHit = true;

	

	m_iShootFrameCnt = 5;
	m_iShootFrameMaxCnt = 4;
	m_iShootCnt = 0;
	m_iShootMaxCnt = 10;
	m_eRenderGroup = GAMEOBJECT;
}

int COnion::Update(void)
{


	if (m_bDead)
	{
	//	Sleep(100);
		m_eCurState = DEAD;

		if (m_eCurState == DEAD && m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CCarrot>::Create());
			return OBJ_DEAD;
		}
	}

	


	Onion_Intro();
	Onion_Intro_Earth();


	Update_Controller();

	Motion_Change();
	Move_Frame();


	Update_Rect();

	return OBJ_NOEVENT;
}

void COnion::Late_Update(void)
{
}

void COnion::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,	// 복사 받을 위치의 좌표 전달(x,y 순서)
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,		// 복사 받을 이미지의 길이 전달(가로, 세로순서)
		(int)m_tInfo.fCY,
		hMemDC,					// 비트맵을 가지고 있는 dc
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,						// 출력할 비트맵 시작 좌표(x,y 순서)
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,			// 복사 할 비트맵 의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));	// 제거할 픽셀의 색상


							//Rectangle(hDC, m_HRect.left + iScrollX, m_HRect.top + iScrollY, m_HRect.right + iScrollX, m_HRect.bottom + iScrollY);
}

void COnion::Release(void)
{
}

void COnion::Collision_Event(CObj * _OtherObj, float fColX, float fColY)
{
	CBullet*	pBullet = dynamic_cast<CBullet*>(_OtherObj);
	if (pBullet)
	{
		m_fHp -= pBullet->Get_Damage();
	}

	if (m_fHp <= EPSILON)
	{
		m_bDead = true;
	}
	/*CCharging_Bullet*	pChargind_Bullet = dynamic_cast<CCharging_Bullet*>(_OtherObj);
	if (pChargind_Bullet)
	{
	m_fHp -= pChargind_Bullet->Get_Damage();
	}*/
}

void COnion::Update_Controller()
{
	if (m_bDead == true)return;

	if (ShootStateTimer.Check())
	{

			m_bShootState = !m_bShootState;
	}

	if (m_bShootState && ShootStateCoolTimer.Check())
	{
	
		m_eCurState = ATTACK;

		if (m_iShootCnt >= m_iShootMaxCnt)
		{
			m_eCurState = IDLE;
		}
	}

	if (ShootTimer.Check())
	{
		m_bShoot_Start = !m_bShoot_Start;
		m_iShootCnt = 0;
	}

	if (m_bShoot_Start && ShootCoolTimer.Check())
	{
		if (m_iShootCnt < m_iShootMaxCnt)
		{
			m_iShootFrameCnt = 0;
			m_iShootCnt++;
		}
	}

	if (m_iShootFrameCnt <= m_iShootFrameMaxCnt)
	{

		if (m_iShootFrameCnt == m_iShootFrameMaxCnt)
		{
			if (GetTickCount() % 6 == 0)
			{
				CObj* pOnion_Parry = CAbstractFactory<COnion_Parry_Bullet>::Create((float)(rand() % WINCX),  100.f, DIR_DOWN);
				CObjMgr::Get_Instance()->Add_Object(OBJ_PARRY, pOnion_Parry);
				CObj* pOnion_Effect = CAbstractFactory<COnion_Bullet_Effect>::Create(m_tInfo.fX - 5.f, (float)m_HRect.top - 50.f);
				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, pOnion_Effect);
			}
			else
			{
			CObj* pOnion = CAbstractFactory<COnion_Bullet>::Create((float)(rand() % WINCX),  100.f, DIR_DOWN);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, pOnion);
			CObj* pOnion_Effect = CAbstractFactory<COnion_Bullet_Effect>::Create(m_tInfo.fX - 5.f, (float)m_HRect.top - 50.f);
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, pOnion_Effect);

			}
		}
		m_iShootFrameCnt++;
		

	}
}

void COnion::Onion_Attack_End(void)
{
	/*if (m_bIsAttackEnd)
	{
		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			m_eCurState = IDLE;
		}
	}*/
}

void COnion::Onion_Idle_End(void)
{
	/*if (m_bIsIdleEnd)
	{
		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			
			m_eCurState = CHANGETOATTACK;
		}
		m_bIsAttackEnd = false;
	}*/
}

void COnion::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case INTRO_EARTH:
			m_pFrameKey = L"Onion_Intro_Earth";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 17;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case INTRO:
			m_tInfo.fCX = 513.f;
			m_tInfo.fCY = 643.f;
			m_pFrameKey = L"Onion_Intro";  
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 23;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 90;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case IDLE:
			m_tInfo.fCX = 496.f;
			m_tInfo.fCY = 563.f;
			m_pFrameKey = L"Onion_Idle";									
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 14;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case BEFORE_ATTACK:
			m_tInfo.fCX = 472.f;
			m_tInfo.fCY = 570.f;
			m_pFrameKey = L"Onion_BeforeAttack";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ATTACK:
			m_tInfo.fCX = 472.f;
			m_tInfo.fCY = 570.f;
			m_pFrameKey = L"Onion_Attack";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 40;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

			// When Collision_Event 
		case CHANGETOATTACK:
			m_tInfo.fCX = 472.f;
			m_tInfo.fCY = 570.f;

			if (m_ePreState == ATTACK)
			{
				m_pFrameKey = L"Onion_ChangeToAttack";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 1;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			else
			{
				m_pFrameKey = L"Onion_ChangeToAttack";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 0;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			break;

			//case HIT:
			//	m_tFrame.iFrameStart = 0;
			//	m_tFrame.iFrameEnd = 1;
			//	m_tFrame.iMotion = 3;
			//	m_tFrame.dwFrameSpeed = 200;
			//	m_tFrame.dwFrameTime = GetTickCount();
			//	break;

		case DEAD:
			m_tInfo.fCX = 524.f;
			m_tInfo.fCY = 630.f;
			m_pFrameKey = L"Onion_Death";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 31;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void COnion::Onion_Intro_Earth(void)
{
	if (m_bIsIntro_First == false) return;

	else if (m_bIsIntro_First)
	{

		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			m_eCurState = INTRO;



			if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
			{
				m_bIsIntro_Second = true;
				m_bIsIntro_First = false;
			}
		}
	}
}

void COnion::Onion_Intro(void)
{
	if (m_bIsIntro_Second == false) return;


	else if (m_bIsIntro_Second)
	{
		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			m_eCurState = IDLE;
			m_bIsIntro_Second = false;
		}
	}
}



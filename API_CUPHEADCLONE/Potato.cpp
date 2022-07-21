#include "stdafx.h"
#include "Potato.h"
#include "ObjMgr.h"
#include "Bullet_Effect.h"
#include "EffectMgr.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Potato_Bullet.h"
#include "Potato_Bullet_Effect.h"
#include "Onion.h"
#include "Potato_Parry_Bullet.h"

CPotato::CPotato()
	:m_eCurState(INTRO_EARTH), m_ePreState(INTRO_EARTH)
{
}


CPotato::~CPotato()
{
	Release();
}

void CPotato::Initialize(void)
{
	m_tInfo = { 1300.f, 675.f, 557.f, 461.f };
	m_HInfo = { 1300.f, 685.f, 262.f, 350.f };

	m_fHp = 3.f;

	//When the Potato Bullet Create
	ShootTimer.InitLoop(5.1f);
	//The Potato Bullet Distance 
	ShootCoolTimer.InitLoop(1.3f);

	ShootStateTimer.InitLoop(5.1f);
	ShootStateCoolTimer.InitLoop(1.1f);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Intro_Earth.bmp", L"Boss_Intro_Earth"); //fCX 557 fCY 461
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Intro.bmp", L"Potato_Intro"); // fCX 526 fCY 512
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Idle.bmp", L"Potato_Idle"); // fCX 526 fCY 512

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Spit_Attack.bmp", L"Potato_Attack");// fCX 526 fCY 512
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Death.bmp", L"Potato_Death"); // fCX 332 fCY 512

	m_pFrameKey = L"Boss_Intro_Earth";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 17;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_dwTimer = GetTickCount();

	m_bIsIntro_First = true;
	m_iShootFrameCnt = 14;
	m_iShootFrameMaxCnt = 13;
	m_iShootCnt = 0;
	m_iShootMaxCnt = 4;

	m_eRenderGroup = GAMEOBJECT;
}

int CPotato::Update(void)
{
	if (m_bDead)
	{
		//Sleep(140);
		m_eCurState = DEAD;
	

		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<COnion>::Create());
			return OBJ_DEAD;
		}
	}

	
	Potato_Intro();
	Potato_Intro_Earth();
	Update_Controller();
	Motion_Change();
	Move_Frame();

	
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPotato::Late_Update(void)
{
}

void CPotato::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		m_tRect.left+ iScrollX,	// 복사 받을 위치의 좌표 전달(x,y 순서)
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

void CPotato::Release(void)
{
}

void CPotato::Collision_Event(CObj * _OtherObj, float fColX, float fColY)
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

void CPotato::Update_Controller()
{
	if (m_bDead) return;

	if (ShootStateTimer.Check())
	{
		m_bShootState = !m_bShootState;
	}


	if (m_bShootState && ShootStateCoolTimer.Check())
	{
		m_eCurState = ATTACK;
		
		if (m_iShootCnt >= m_iShootMaxCnt)
			m_eCurState = IDLE;
		
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
			if (m_iShootCnt == 4)
			{
				CObj* pPotato = CAbstractFactory<CPotato_Parry_Bullet>::Create(m_HInfo.fX - 150, m_HInfo.fY + 160, DIR_LEFT);
				CObjMgr::Get_Instance()->Add_Object(OBJ_PARRY, pPotato);
				CObj* pPotato_Effect = CAbstractFactory<CPotato_Bullet_Effect>::Create(m_HInfo.fX - 180, m_HInfo.fY + 100);
				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, pPotato_Effect);
			}
		else
		{
			CObj* pPotato = CAbstractFactory<CPotato_Bullet>::Create(m_HInfo.fX - 150, m_HInfo.fY + 160, DIR_LEFT);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, pPotato);
			CObj* pPotato_Effect = CAbstractFactory<CPotato_Bullet_Effect>::Create(m_HInfo.fX - 180, m_HInfo.fY + 100);
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, pPotato_Effect);

		}
		}
		m_iShootFrameCnt++;
	}
}



void CPotato::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case INTRO_EARTH:
			m_pFrameKey = L"Potato_Intro_Earth";  
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 17;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case INTRO:
			m_tInfo.fCX = 526.f;
			m_tInfo.fCY = 512.f;
			m_pFrameKey = L"Potato_Intro";   // fCX 526 fCY 512 
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 90;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case IDLE:
			m_tInfo.fCX = 526.f;
			m_tInfo.fCY = 512.f;
			m_pFrameKey = L"Potato_Idle";   // fCX 526 fCY 512 
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ATTACK:
			m_pFrameKey = L"Potato_Attack";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 23;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 35;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		//case HIT:
		//	m_tFrame.iFrameStart = 0;
		//	m_tFrame.iFrameEnd = 1;
		//	m_tFrame.iMotion = 3;
		//	m_tFrame.dwFrameSpeed = 200;
		//	m_tFrame.dwFrameTime = GetTickCount();
		//	break;

		case DEAD:
			m_tInfo.fCX = 332.f;
			m_tInfo.fCY = 512.f;
			m_pFrameKey = L"Potato_Death";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CPotato::Potato_Intro_Earth(void)
{
	if (m_bIsIntro_First)
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


void CPotato::Potato_Intro(void)
{
	if (m_bIsIntro_Second)
	{
		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			m_eCurState = IDLE;
			m_bIsIntro_Second = false;
		}
	}
}

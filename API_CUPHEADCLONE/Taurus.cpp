#include "stdafx.h"
#include "Taurus.h"
#include "ObjMgr.h"
#include "Bullet_Effect.h"
#include "EffectMgr.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CTaurus::CTaurus()
	: m_eCurState(INTRO_STAR), m_ePreState(INTRO_STAR)
{
}


CTaurus::~CTaurus()
{
	Release();
}

void CTaurus::Initialize(void)
{
	m_tInfo.fCX = 700.f;
	m_tInfo.fCY = 700.f;

	m_HInfo.fCX = 700.f;
	m_HInfo.fCY = 700.f;
	

	m_fHp = 3.f;

	//When the Potato Bullet Create
	ShootTimer.InitLoop(5.1f);
	//The Potato Bullet Distance 
	ShootCoolTimer.InitLoop(1.3f);

	ShootStateTimer.InitLoop(5.1f);
	ShootStateCoolTimer.InitLoop(1.1f);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Taurus/Taurus_Idle.bmp", L"Taurus_Idle"); 
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Taurus/Taurus_Attack.bmp", L"Taurus_Attack"); 


	m_pFrameKey = L"Taurus_Idle";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_dwTimer = GetTickCount();

	m_bIsIntro_First = true;


	m_eRenderGroup = GAMEOBJECT;
}

int CTaurus::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	Taurus_Intro();
	Taurus_Intro_Star();

	Update_Controller();
	Motion_Change();
	Move_Frame();


	Update_Rect();

	return OBJ_NOEVENT;
}

void CTaurus::Late_Update(void)
{
}

void CTaurus::Render(HDC hDC)
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
		RGB(1, 1, 1));	// 제거할 픽셀의 색상

		//Rectangle(hDC, m_HRect.left + iScrollX, m_HRect.top + iScrollY, m_HRect.right + iScrollX, m_HRect.bottom + iScrollY);
}

void CTaurus::Release(void)
{
}

void CTaurus::Collision_Event(CObj * _OtherObj, float fColX, float fColY)
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
}

void CTaurus::Update_Controller()
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
		// 돌진 구현하기 
	}

}

void CTaurus::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case INTRO_STAR:
			m_pFrameKey = L"Taurus_Idle";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case INTRO:
			m_pFrameKey = L"Taurus_Idle";  
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.iMotion = 1;
			m_tFrame.dwFrameSpeed = 90;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case IDLE:
			m_pFrameKey = L"Taurus_Idle";   
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.iMotion = 2;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ATTACK:
			m_tInfo.fCX = 1200.f;
			m_tInfo.fCY = 500.f;
			m_pFrameKey = L"Taurus_Attack";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 20;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 70;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CTaurus::Taurus_Intro_Star(void)
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

void CTaurus::Taurus_Intro(void)
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

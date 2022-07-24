#include "stdafx.h"
#include "BasicBullet.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Player.h"
#include "Potato.h"
#include "ObjMgr.h"
#include "Bullet_Effect.h"
#include "AbstractFactory.h"
#include "LineMgr.h"
#include "Bullet_Death.h"

CBasicBullet::CBasicBullet()
	:	m_eCurState(BIRTH), m_ePreState(BIRTH)
{
}


CBasicBullet::~CBasicBullet()
{
	Release();
}

void CBasicBullet::Initialize(void)
{
	m_tInfo.fCX = 95.f;
	m_tInfo.fCY = 89.f;

	m_HInfo.fCX = 50.f;
	m_HInfo.fCY = 50.f;
	m_HInfo.m_fDamage = 1.f;
	m_fSpeed = 30.f;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Bullet/Default/BulletLeftRight.bmp", L"BulletLeftRight"); // 좌우
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Bullet/Default/BulletUpLeftRight.bmp", L"BulletUpLeftRight"); // 좌우 대각선
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Bullet/Default/BulletUpDown.bmp", L"BulletUpDown"); // 위
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Bullet/Default/BulletStart.bmp", L"BulletStart"); // BIRTH
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Bullet/Default/BulletDeath.bmp", L"BulletDeath"); // DEAD
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Bullet/Default/BulletDeath.bmp", L"BulletDeath"); // 
	m_pFrameKey = L"BulletStart";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 30;
	m_tFrame.dwFrameTime = GetTickCount();
	m_bFirstIntro = true;
	m_eRenderGroup = GAMEOBJECT;

}

int CBasicBullet::Update(void)
{
	if (m_bDead)
	{
		if(m_eCurState == DEAD && m_tFrame.iFrameStart>= m_tFrame.iFrameEnd)
		return OBJ_DEAD;
	}

	Bullet_Intro();



	if (m_eCurState == ATTACK)
	{
		switch (m_eDir)
		{
		case DIR_LEFT:
			m_tInfo.fX -= m_fSpeed;
			m_HInfo.fX -= m_fSpeed;
			break;

		case DIR_RIGHT:
			m_tInfo.fX += m_fSpeed;
			m_HInfo.fX += m_fSpeed;
			break;

		case DIR_UP:
			m_tInfo.fY -= m_fSpeed;
			m_HInfo.fY -= m_fSpeed;
			break;

		case DIR_LU:
			m_tInfo.fX -= m_fSpeed;
			m_HInfo.fX -= m_fSpeed;

			m_tInfo.fY -= m_fSpeed;
			m_HInfo.fY -= m_fSpeed;
			break;

		case DIR_RU:
			m_tInfo.fX += m_fSpeed;
			m_HInfo.fX += m_fSpeed;

			m_tInfo.fY -= m_fSpeed;
			m_HInfo.fY -= m_fSpeed;
			break;
		}
	}

	Motion_Change();
	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;

}

void CBasicBullet::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case BIRTH:
			m_pFrameKey = L"BulletStart";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case DEAD:
			m_pFrameKey = L"BulletDeath";
			m_tInfo.fCX = 280.f;
			m_tInfo.fCY = 280.f;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ATTACK:
			if (m_eDir == DIR_LEFT)
			{
				m_pFrameKey = L"BulletLeftRight";
				m_tInfo.fCX = 142.f;
				m_tInfo.fCY = 30.f;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 0;
				m_tFrame.dwFrameSpeed = 60;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			else if (m_eDir == DIR_RIGHT)
			{
				m_pFrameKey = L"BulletLeftRight";
				m_tInfo.fCX = 142.f;
				m_tInfo.fCY = 30.f;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 1;
				m_tFrame.dwFrameSpeed = 60;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			else if (m_eDir == DIR_LU)
			{
				m_pFrameKey = L"BulletUpLeftRight";
				m_tInfo.fCX = 162.f;
				m_tInfo.fCY = 92.f;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 0;
				m_tFrame.dwFrameSpeed = 60;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			else if (m_eDir == DIR_RU)
			{
				m_pFrameKey = L"BulletUpLeftRight";
				m_tInfo.fCX = 162.f;
				m_tInfo.fCY = 92.f;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 1;
				m_tFrame.dwFrameSpeed = 60;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			else if (m_eDir == DIR_UP)
			{
				m_pFrameKey = L"BulletUpDown";
				m_tInfo.fCX = 30.f;
				m_tInfo.fCY = 142.f;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 1;
				m_tFrame.dwFrameSpeed = 60;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			break;

		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CBasicBullet::Bullet_Intro(void)
{
	if (m_bFirstIntro)
	{

		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			m_eCurState = ATTACK;

			if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
			{
				m_bFirstIntro = false;
			}
		}
	}
}


void CBasicBullet::Late_Update(void)
{
	if (m_tInfo.fX >= 7500 || m_tInfo.fX <= 0 || m_tInfo.fY <= 0)
		m_bDead = true;
}

void CBasicBullet::Render(HDC hDC)
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
}

void CBasicBullet::Collision_Event(CObj * _OtherObj, float _fColX, float _fColY)
{
	CMonster* pMonster = dynamic_cast<CMonster*>(_OtherObj);
	if (pMonster)
	{
		m_bDead = true;
		m_eCurState = DEAD;
	}
}


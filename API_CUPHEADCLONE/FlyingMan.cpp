#include "stdafx.h"
#include "FlyingMan.h"
#include "ObjMgr.h"
#include "Bullet_Effect.h"
#include "EffectMgr.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Player.h"
#include "LineMgr.h"


CFlyingMan::CFlyingMan()
	:m_eCurState(INTRO_AIR), m_ePreState(MOTION_END), m_eState(AIR)
{
}


CFlyingMan::~CFlyingMan()
{
	Release();
}

void CFlyingMan::Initialize(void)
{
	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 300.f;

	m_HInfo.fCX = 200.f;
	m_HInfo.fCY = 150.f;
	m_fSpeed = 6.f;
	m_fHp = 3.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Enemy/Flying_Man/Flying_Man.bmp", L"Flying_Man"); 
	
	m_pFrameKey = L"Flying_Man";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 14;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_dwTimer = GetTickCount();


	m_eRenderGroup = GAMEOBJECT;
}

int CFlyingMan::Update(void)
{
	m_bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_HInfo.fX, m_HInfo.fY, &m_fFootY);

	float fCurFootY = m_HInfo.fY + m_HInfo.fCY * 0.5f;

	switch (m_eState)
	{
	case AIR:
		m_tInfo.fY -= m_fCurJumpSpeed;
		m_HInfo.fY -= m_fCurJumpSpeed;

		if (fabs(m_fCurJumpSpeed) < m_fMaxAbsJumpSpeed) // limit max speed
		{
			m_fCurJumpSpeed -= 1.f;
		}
		break;

	case GROUND:
		m_fCurJumpSpeed = 0.f;
		m_HInfo.fY = m_fFootY - m_HInfo.fCY * 0.5f;
		m_tInfo.fY = m_fFootY - m_tInfo.fCY * 0.5f;
		m_eCurState = WALK;
		break;
	}

	fCurFootY = m_HInfo.fY + m_HInfo.fCY * 0.5f;

	if (m_bLineCol && abs(m_fFootY - fCurFootY) < m_fMaxAbsJumpSpeed * 0.8f)
	{
		m_eState = GROUND;
		m_eCurState = WALK;
	}
	else
		m_eState = AIR;

	if (m_eCurState == WALK)
	{
		m_tInfo.fX -= m_fSpeed;
		m_HInfo.fX -= m_fSpeed;
	}



	Motion_Change();
	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;


}

void CFlyingMan::Late_Update(void)
{
	if (m_tInfo.fY > 1300)
		m_bDead = true;
}

void CFlyingMan::Render(HDC hDC)
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
		RGB(250, 0, 250));	// 제거할 픽셀의 색상
}

void CFlyingMan::Release(void)
{
}

void CFlyingMan::Collision_Event(CObj * _OtherObj, float fColX, float fColY)
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

void CFlyingMan::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case INTRO_AIR:
			m_pFrameKey = L"Flying_Man";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 14;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case LAND:
			if (m_eState == GROUND && !m_bIsIntro_First)
			{
				m_pFrameKey = L"Flying_Man";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 10;
				m_tFrame.iMotion = 1;
				m_tFrame.dwFrameSpeed = 60;
				m_tFrame.dwFrameTime = GetTickCount();
				m_bIsIntro_First = true;
			}
			break;

		case WALK:
			m_pFrameKey = L"Flying_Man";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 14;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}
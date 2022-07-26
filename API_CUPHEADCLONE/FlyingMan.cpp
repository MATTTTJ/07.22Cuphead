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
#include "Monster_Dead_Effect.h"

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

	m_HInfo.fCX = 80.f;
	m_HInfo.fCY = 140.f;
	m_fSpeed = 4.f;
	m_fHp = 1.f;
	CSoundMgr::Get_Instance()->PlaySound(L"Flowerman_drop.wav", SOUND_EFFECT, 1.f);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Enemy/Flying_Man/Flying_Man.bmp", L"Flying_Man"); 
	
	m_pFrameKey = L"Flying_Man";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 14;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_dwTimer = GetTickCount();

	m_bFirstRender = false;
	m_bIsIntro_First = true;
	m_eRenderGroup = GAMEOBJECT;
}

int CFlyingMan::Update(void)
{
	if (m_bDead)
	{
		if (m_tFrame.iFrameStart == 0)
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonster_Dead_Effect>::Create(m_tInfo.fX + (rand() % 300), m_tInfo.fY + (rand() % 300)));
		return OBJ_DEAD;
	}
	if (m_eCurState == WALK)
	{
		m_tInfo.fX -= m_fSpeed;
		m_HInfo.fX -= m_fSpeed;
	}

	if (m_eCurState == LAND && m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		m_eCurState = WALK;


	Ground_Check();

	Motion_Change();
	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;


}

void CFlyingMan::Late_Update(void)
{
	if (m_tInfo.fY > 1300 || m_tInfo.fX < 0)
		m_bDead = true;
}

void CFlyingMan::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	if (m_bFirstRender)
	{
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
			RGB(250, 250, 250));	// 제거할 픽셀의 색상
	}
	m_bFirstRender = true;
	//Rectangle(hDC, m_HRect.left + iScrollX, m_HRect.top + iScrollY, m_HRect.right + iScrollX, m_HRect.bottom + iScrollY);
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
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonster_Dead_Effect>::Create((float)m_HInfo.fX - 50.f, m_HInfo.fY - 40.f));

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
			m_tFrame.iMotion = 2;
			m_tFrame.dwFrameSpeed = 60;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CFlyingMan::Ground_Check(void)
{
	m_bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_HInfo.fX, m_HInfo.fY, &m_fFootY);

	float fCurFootY = m_tInfo.fY + m_tInfo.fCY * 0.5f;

	switch (m_eState)
	{
	case AIR:
		m_tInfo.fY -= m_fCurJumpSpeed;
		m_HInfo.fY -= m_fCurJumpSpeed;
		m_tInfo.fX -= 2.f;
		m_HInfo.fX -= 2.f;

		if (fabs(m_fCurJumpSpeed) < m_fMaxAbsJumpSpeed) // limit max speed
		{
			m_fCurJumpSpeed -= 0.2f;

		}
		break;

	case GROUND:
		m_fCurJumpSpeed = 0.f;
		m_HInfo.fY = m_fFootY - m_HInfo.fCY * 0.5f;
		m_tInfo.fY = m_fFootY - m_tInfo.fCY * 0.25f;
		break;
	default:
		break;
	}

	fCurFootY = m_HInfo.fY + m_HInfo.fCY * 0.5f;

	if (m_bLineCol && abs(m_fFootY - fCurFootY) < m_fMaxAbsJumpSpeed * 0.8f)
	{
		m_eState = GROUND;

		if (m_bIsIntro_First)
		{
			m_eCurState = LAND;
			m_bIsIntro_First = false;
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"Flowerman_landing.wav", SOUND_EFFECT, 1.f);

		}
	}
	else
		m_eState = AIR;
}

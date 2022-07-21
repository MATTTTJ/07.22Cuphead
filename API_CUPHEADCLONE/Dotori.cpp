#include "stdafx.h"
#include "Dotori.h"
#include "ObjMgr.h"
#include "Bullet_Effect.h"
#include "EffectMgr.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Player.h"

CDotori::CDotori()
{
}


CDotori::~CDotori()
{
	Release();
}

void CDotori::Initialize(void)
{
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 150.f;

	m_HInfo.fCX = 140.f;
	m_HInfo.fCY = 140.f;

	m_fSpeed = 8.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Enemy/ButterFly/BF_Pink.bmp", L"BF_Pink");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Intro.bmp", L"Potato_Intro"); // fCX 526 fCY 512
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Idle.bmp", L"Potato_Idle"); // fCX 526 fCY 512

	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Spit_Attack.bmp", L"Potato_Attack");// fCX 526 fCY 512
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Death.bmp", L"Potato_Death"); // fCX 332 fCY 512

	m_pFrameKey = L"BF_Pink";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 23;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_dwTimer = GetTickCount();

	m_eRenderGroup = GAMEOBJECT;
}

int CDotori::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	if (PlayerDetect(300.f))
	{
		m_bDetected = true;
	}

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	if (m_bDetected)
	{

		float	fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
		float	fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

		m_fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		fWidth /= m_fDiagonal;
		fHeight /= m_fDiagonal;

		m_tInfo.fX += m_fSpeed * fWidth;
		m_tInfo.fY += m_fSpeed * fHeight;
	}
	else
	{
		if (m_eDir == DIR_LEFT)
		{
			m_tInfo.fX -= m_fSpeed;
		}
		if (m_eDir == DIR_RIGHT)
		{
			m_tInfo.fX += m_fSpeed;
		}
	}

	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CDotori::Late_Update(void)
{
	if (m_tInfo.fCY < 0)
		m_bDead = true;
}

void CDotori::Render(HDC hDC)
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
}

void CDotori::Release(void)
{
}

void CDotori::Collision_Event(CObj * _OtherObj, float fColX, float fColY)
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

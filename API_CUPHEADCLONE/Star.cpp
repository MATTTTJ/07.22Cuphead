#include "stdafx.h"
#include "Star.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Cloud.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Cloud_Dead.h"
#include "DeadEventMgr.h"
#include "Bullet.h"
CStar::CStar()
{
}


CStar::~CStar()
{
	Release();
}

void CStar::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Sagittarius/Star_BP.bmp", L"Star_BP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Sagittarius/Star_Dead.bmp", L"Star_Dead");

	m_MTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_MONSTER, this);
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	m_pFrameKey = L"Star_BP";

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_HInfo.fCX = 40.f;
	m_HInfo.fCY = 40.f;

	m_fHp = 1.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 12;
	m_tFrame.iMotion = 1;
	m_tFrame.dwFrameSpeed = 70;
	m_tFrame.dwFrameTime = GetTickCount();

	m_fDiagonal = 300.f;
	m_fSpeed = 2.5f;
	m_dwChaserTime = GetTickCount();
	Update_Rect();

	m_eRenderGroup = GAMEOBJECT;
}

int CStar::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	switch (m_eDir)
	{
	case DIR_LEFT:
		m_fAngle += m_fSpeed;

		m_tInfo.fX = m_MTarget->Get_Info().fX + m_fDiagonal * cosf(m_fAngle * (PI / 180.f));
		m_tInfo.fY = m_MTarget->Get_Info().fY - m_fDiagonal * sinf(m_fAngle * (PI / 180.f));
		break;
	
	case DIR_RIGHT:
		
		if (m_dwChaserTime + 50 < GetTickCount())
		{
			m_tInfo.fX = m_pTarget->Get_Info().fX * 0.5f + m_fDiagonal * cosf(m_fAngle * (PI / 180.f));
			m_tInfo.fY = m_pTarget->Get_Info().fY * 0.5f - m_fDiagonal * sinf(m_fAngle * (PI / 180.f));
		}
		m_dwChaserTime = GetTickCount();
		break;
	default:
		break;
	}
	

	//m_tInfo.fX -= m_fSpeed;
	//m_HInfo.fX -= m_fSpeed;

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CStar::Late_Update(void)
{
	
}

void CStar::Render(HDC hDC)
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
		RGB(255, 255, 255));	// 제거할 픽셀의 색상

}

void CStar::Release(void)
{
}

void CStar::Collision_Event(CObj * _OtherObj, float fColX, float fColY)
{
	CBullet*	pBullet = dynamic_cast<CBullet*>(_OtherObj);

	if (pBullet)
	{
		if (pBullet->Get_Dead()) return;
		m_fHp -= pBullet->Get_Damage();

		if (m_fHp <= EPSILON)
		{
			m_bDead = true;
		}
	}
}

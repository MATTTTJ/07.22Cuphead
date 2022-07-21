#include "stdafx.h"
#include "Potato_Parry_Bullet.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Player.h"
#include "Potato.h"
#include "ObjMgr.h"
#include "Bullet_Effect.h"
#include "AbstractFactory.h"

CPotato_Parry_Bullet::CPotato_Parry_Bullet()
{
}


CPotato_Parry_Bullet::~CPotato_Parry_Bullet()
{
	Release();
}

void CPotato_Parry_Bullet::Initialize(void)
{

	m_tInfo.fCX = 132.f;
	m_tInfo.fCY = 142.f;

	m_HInfo.fCX = 132.f;
	m_HInfo.fCY = 142.f;

	m_HInfo.m_fDamage = 1.f;
	m_fSpeed = 6.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Parryable.bmp", L"Potato_Parryable");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Parryable.bmp", L"Parryable");

	m_pFrameKey = L"Potato_Parryable";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 60;
	m_tFrame.dwFrameTime = GetTickCount();


	m_eRenderGroup = GAMEOBJECT;

}

int CPotato_Parry_Bullet::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	switch (m_eDir)
	{
	case DIR_LEFT:
		m_tInfo.fX -= m_fSpeed;
		m_HInfo.fX -= m_fSpeed;


		break;
	}
	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;

}

void CPotato_Parry_Bullet::Late_Update(void)
{
	if (-100 >= m_tRect.left)
	{
		m_bDead = true;
	}
}

void CPotato_Parry_Bullet::Render(HDC hDC)
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

void CPotato_Parry_Bullet::Release(void)
{
}

void CPotato_Parry_Bullet::Collision_Event(CObj * _OtherObj, float _fColX, float _fColY)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_OtherObj);
	if (pPlayer)
	{
		m_bDead = true;
	}
}

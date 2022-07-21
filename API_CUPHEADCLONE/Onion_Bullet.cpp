#include "stdafx.h"
#include "Onion_Bullet.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Player.h"
#include "Potato.h"
#include "ObjMgr.h"
#include "Bullet_Effect.h"
#include "AbstractFactory.h"
#include "Tears_Splash_Effect.h"


COnion_Bullet::COnion_Bullet()
{
}


COnion_Bullet::~COnion_Bullet()
{
	Release();
}

void COnion_Bullet::Initialize(void)
{
	
	m_tInfo.fCX = 37.f;
	m_tInfo.fCY = 68.f;

	m_HInfo.fCX = 37.f;
	m_HInfo.fCY = 68.f;

	m_HInfo.m_fDamage = 1.f;
	m_fSpeed = 6.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Onion/Onion_Proj_NonParryableA.bmp", L"NonParryable_A");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Onion/Onion_Proj_NonParryableB.bmp", L"NonParryable_B");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Onion/Onion_Proj_NonParryableC.bmp", L"NonParryable_C");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Onion/Onion_Proj_NonParryableD.bmp", L"NonParryable_D");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Onion/Onion_Proj_NonParryableE.bmp", L"NonParryable_E");
	
	m_pFrameKey = L"NonParryable_A";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 40;
	m_tFrame.dwFrameTime = GetTickCount();

	m_bFistSpawn = false;

	

	m_eRenderGroup = GAMEOBJECT;
}

int COnion_Bullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;



	switch (m_eDir)
	{
	case DIR_DOWN:
		m_tInfo.fY += m_fSpeed;
		m_HInfo.fY += m_fSpeed;
		break;
	}

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}


void COnion_Bullet::Late_Update(void)
{
	if ( 750 <= m_HRect.bottom)
	{
		m_bDead = true;
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CTears_Splash_Effect>::Create(m_tInfo.fX, m_tInfo.fY));
	}
}

void COnion_Bullet::Render(HDC hDC)
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

void COnion_Bullet::Release(void)
{
}

void COnion_Bullet::Collision_Event(CObj * _OtherObj, float _fColX, float _fColY)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_OtherObj);
	if (pPlayer)
	{
		m_bDead = true;

		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CTears_Splash_Effect>::Create(m_tInfo.fX, m_tInfo.fY));
	}
}




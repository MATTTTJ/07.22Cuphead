#include "stdafx.h"
#include "ButterFly.h"
#include "ObjMgr.h"
#include "Bullet_Effect.h"
#include "EffectMgr.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Player.h"

CButterFly::CButterFly()
{
}


CButterFly::~CButterFly()
{
	Release();
}

void CButterFly::Initialize(void)
{
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_HInfo.fCX = 70.f;
	m_HInfo.fCY = 70.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Enemy/ButterFly/BF_Puple.bmp", L"BF_Puple");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Intro.bmp", L"Potato_Intro"); // fCX 526 fCY 512
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Idle.bmp", L"Potato_Idle"); // fCX 526 fCY 512

	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Spit_Attack.bmp", L"Potato_Attack");// fCX 526 fCY 512
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Death.bmp", L"Potato_Death"); // fCX 332 fCY 512

	m_pFrameKey = L"BF_Puple";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 23;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_dwTimer = GetTickCount();

	m_eRenderGroup = GAMEOBJECT;
}

int CButterFly::Update(void)
{
	//움직이는 것만 넣기
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

void CButterFly::Late_Update(void)
{
}

void CButterFly::Render(HDC hDC)
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

void CButterFly::Release(void)
{
}

void CButterFly::Collision_Event(CObj * _OtherObj, float fColX, float fColY)
{
	/*CPlayer* pPlayer = dynamic_cast<CPlayer*>(_OtherObj);
	if (pPlayer)
	{
		m_bDead = true;
	}*/
}

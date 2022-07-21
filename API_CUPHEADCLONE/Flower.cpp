#include "stdafx.h"
#include "Flower.h"
#include "ObjMgr.h"
#include "Bullet_Effect.h"
#include "EffectMgr.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Player.h"

CFlower::CFlower()
	: m_eCurState(IDLE), m_ePreState(MOTION_END)
{
}


CFlower::~CFlower()
{
	Release();
}

void CFlower::Initialize(void)
{
	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 200.f;

	m_HInfo.fCX = 140.f;
	m_HInfo.fCY = 200.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Enemy/Flower/Flower.bmp", L"Flower");
	
	m_pFrameKey = L"Flower";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 23;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_dwTimer = GetTickCount();

	m_eRenderGroup = GAMEOBJECT;
}

int CFlower::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (PlayerDetect(300.f))
	{
		m_eCurState = ATTACK;
		// 플레이어가 왼쪽인지 오른쪽인지 판단하고 그쪽으로 총알 발사구현
	}
	else
		m_eCurState = IDLE;

	Motion_Change();
	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CFlower::Late_Update(void)
{
}

void CFlower::Render(HDC hDC)
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

void CFlower::Release(void)
{
}

void CFlower::Collision_Event(CObj * _OtherObj, float fColX, float fColY)
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

void CFlower::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_pFrameKey = L"Flower";   // fCX 526 fCY 512 
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ATTACK:
			m_pFrameKey = L"Flower";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 13;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		default:
			break;
		}
	}
}

#include "stdafx.h"
#include "JumpEnemy.h"
#include "ObjMgr.h"
#include "Bullet_Effect.h"
#include "EffectMgr.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Player.h"

CJumpEnemy::CJumpEnemy()
{
}


CJumpEnemy::~CJumpEnemy()
{
	Release();
}

void CJumpEnemy::Initialize(void)
{

	m_tInfo.fCX = 450.f;
	m_tInfo.fCY = 450.f;

	m_HInfo.fCX = 300.f;
	m_HInfo.fCY = 300.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Enemy/Jump_Enemy/Jump_Enemy.bmp", L"Jump_Enemy");

	m_pFrameKey = L"Jump_Enemy";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 19;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_dwTimer = GetTickCount();

	m_fCurJumpSpeed = m_fInitJumpSpeed;
	m_eRenderGroup = GAMEOBJECT;
}

int CJumpEnemy::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fY -= m_fCurJumpSpeed;
	m_HInfo.fY -= m_fCurJumpSpeed;

	if (PlayerDetect(500.f))
	{
		m_bDetected = true;
	}

	if (fabs(m_fCurJumpSpeed) < m_fMaxAbsJumpSpeed) // limit max speed
		m_fCurJumpSpeed -= GRAVITY;

	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CJumpEnemy::Late_Update(void)
{
	if (m_bDetected && !m_bIsIntro_First)
	{
		m_fCurJumpSpeed = m_fInitJumpSpeed;
		m_bIsIntro_First = true;
	}
	
	if (m_tInfo.fY > 1300)
		m_bDead = true;
}

void CJumpEnemy::Render(HDC hDC)
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
		RGB(250, 250, 250));	// 제거할 픽셀의 색상
}

void CJumpEnemy::Release(void)
{
}

void CJumpEnemy::Collision_Event(CObj * _OtherObj, float fColX, float fColY)
{
}

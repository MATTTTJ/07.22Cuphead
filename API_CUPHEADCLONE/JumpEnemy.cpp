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
		m_tRect.left + iScrollX,	// ���� ���� ��ġ�� ��ǥ ����(x,y ����)
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,		// ���� ���� �̹����� ���� ����(����, ���μ���)
		(int)m_tInfo.fCY,
		hMemDC,					// ��Ʈ���� ������ �ִ� dc
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,						// ����� ��Ʈ�� ���� ��ǥ(x,y ����)
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,			// ���� �� ��Ʈ�� �� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(250, 250, 250));	// ������ �ȼ��� ����
}

void CJumpEnemy::Release(void)
{
}

void CJumpEnemy::Collision_Event(CObj * _OtherObj, float fColX, float fColY)
{
}

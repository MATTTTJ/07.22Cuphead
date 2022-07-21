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
#include "Flower_Bullet.h"

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


	ShootTimer.InitLoop(5.1f);
	//The Potato Bullet Distance 
	ShootCoolTimer.InitLoop(1.3f);

	ShootStateTimer.InitLoop(5.1f);
	ShootStateCoolTimer.InitLoop(1.1f);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Enemy/Flower/Flower.bmp", L"Flower");
	
	m_pFrameKey = L"Flower";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 23;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_dwTimer = GetTickCount();

	m_iShootCnt = 0;
	m_iShootMaxCnt = 2;
	m_iShootFrameCnt = 6;
	m_iShootFrameMaxCnt = 13;
	m_eRenderGroup = GAMEOBJECT;
}

int CFlower::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	
	Update_Controller();
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
		m_tRect.left + iScrollX,	// ���� ���� ��ġ�� ��ǥ ����(x,y ����)
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,		// ���� ���� �̹����� ���� ����(����, ���μ���)
		(int)m_tInfo.fCY,
		hMemDC,					// ��Ʈ���� ������ �ִ� dc
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,						// ����� ��Ʈ�� ���� ��ǥ(x,y ����)
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,			// ���� �� ��Ʈ�� �� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(1, 1, 1));	// ������ �ȼ��� ����
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

void CFlower::Update_Controller()
{
	if (m_bDead) return;

	if (ShootStateTimer.Check())
	{
		m_bShootState = !m_bShootState;
	}


	if (m_bShootState && ShootStateCoolTimer.Check())
	{
		m_eCurState = ATTACK;

		if (m_iShootCnt >= m_iShootMaxCnt)
			m_eCurState = IDLE;

	}

	if (ShootTimer.Check())
	{
		m_bShoot_Start = !m_bShoot_Start;
		m_iShootCnt = 0;
	}

	if (m_bShoot_Start && ShootCoolTimer.Check())
	{
		if (m_iShootCnt < m_iShootMaxCnt)
		{

			m_iShootFrameCnt = 0;
			m_iShootCnt++;

		}
	}

	if (m_iShootFrameCnt <= m_iShootFrameMaxCnt)
	{
		if (m_iShootFrameCnt == m_iShootFrameMaxCnt)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, CAbstractFactory<CFlower_Bullet>::Create(m_tInfo.fX, (float)m_tRect.top + 20.f, DIR_RIGHT));
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, CAbstractFactory<CFlower_Bullet>::Create(m_tInfo.fX, (float)m_tRect.top + 20.f, DIR_LEFT));
		}
		m_iShootFrameCnt++;
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
			m_tFrame.dwFrameSpeed = 80;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ATTACK:
			m_pFrameKey = L"Flower";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 13;
			m_tFrame.iMotion = 1;
			m_tFrame.dwFrameSpeed = 70;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		default:
			break;
		}
		m_eCurState = m_ePreState;
	}
}

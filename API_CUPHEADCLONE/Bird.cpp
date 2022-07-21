#include "stdafx.h"
#include "Bird.h"
#include "ObjMgr.h"
#include "Bullet_Effect.h"
#include "EffectMgr.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CBird::CBird()
{
}


CBird::~CBird()
{
	Release();
}

void CBird::Initialize(void)
{
	m_tInfo = { 1000.f, 525.f, 200.f, 200.f };
	m_HInfo = { 1000.f, 535.f, 150.f, 150.f };

	m_fHp = 2.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Enemy/Bird/Bird.bmp", L"Bird");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Intro.bmp", L"Potato_Intro"); // fCX 526 fCY 512
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Idle.bmp", L"Potato_Idle"); // fCX 526 fCY 512

	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Spit_Attack.bmp", L"Potato_Attack");// fCX 526 fCY 512
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Death.bmp", L"Potato_Death"); // fCX 332 fCY 512

	m_pFrameKey = L"Bird";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 15;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_dwTimer = GetTickCount();

	m_eRenderGroup = GAMEOBJECT;
}

int CBird::Update(void)
{
	if (m_bDead)
	{
		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<COnion>::Create());
			return OBJ_DEAD;
		}
	}

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CBird::Late_Update(void)
{
}

void CBird::Render(HDC hDC)
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

void CBird::Release(void)
{
}

void CBird::Collision_Event(CObj * _OtherObj, float fColX, float fColY)
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
	/*CCharging_Bullet*	pChargind_Bullet = dynamic_cast<CCharging_Bullet*>(_OtherObj);
	if (pChargind_Bullet)
	{
	m_fHp -= pChargind_Bullet->Get_Damage();
	}*/
}



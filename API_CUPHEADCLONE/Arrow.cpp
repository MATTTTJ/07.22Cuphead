#include "stdafx.h"
#include "Arrow.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Player.h"
#include "Potato.h"
#include "ObjMgr.h"
#include "Bullet_Effect.h"
#include "AbstractFactory.h"

CArrow::CArrow()
{
}


CArrow::~CArrow()
{
	Release();
}

void CArrow::Initialize(void)
{
	m_tInfo.fCX = 500.f;
	m_tInfo.fCY = 100.f;

	m_HInfo.fCX = 100.f;
	m_HInfo.fCY = 10.f;

	m_HInfo.m_fDamage = 1.f;
	m_fSpeed = 35.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Sagittarius/Arrow_Idle.bmp", L"Arrow_Idle");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Parryable.bmp", L"Parryable");

	m_pFrameKey = L"Arrow_Idle";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 25;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = GAMEOBJECT;
}

int CArrow::Update(void)
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

void CArrow::Late_Update(void)
{
	if (m_tInfo.fX <= 3000)
	{
		m_bDead = true;
	}
}

void CArrow::Render(HDC hDC)
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

		Rectangle(hDC, m_HRect.left + iScrollX, m_HRect.top + iScrollY, m_HRect.right + iScrollX, m_HRect.bottom + iScrollY);

}

void CArrow::Release(void)
{
}

void CArrow::Collision_Event(CObj * _OtherObj, float _fColX, float _fColY)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_OtherObj);
	if (pPlayer)
	{
		m_bDead = true;
	}
}

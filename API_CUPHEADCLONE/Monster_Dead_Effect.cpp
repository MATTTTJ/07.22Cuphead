#include "stdafx.h"
#include "Monster_Dead_Effect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CMonster_Dead_Effect::CMonster_Dead_Effect()
{
}


CMonster_Dead_Effect::~CMonster_Dead_Effect()
{
}

void CMonster_Dead_Effect::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Taurus/Dash_Effect.bmp", L"TDash_Effect");

	m_pFrameKey = L"TDash_Effect";

	m_tInfo.fCX = 680.f;
	m_tInfo.fCY = 726.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 10;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 50;

	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = EFFECT;
}

int CMonster_Dead_Effect::Update(void)
{
	Move_Frame(10);
	Update_Rect();

	if (m_tFrame.iFrameStart >= 10)
		return OBJ_DEAD;



	return OBJ_NOEVENT;
}

void CMonster_Dead_Effect::Late_Update(void)
{
	
}

void CMonster_Dead_Effect::Render(HDC hDC)
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

void CMonster_Dead_Effect::Release(void)
{
}

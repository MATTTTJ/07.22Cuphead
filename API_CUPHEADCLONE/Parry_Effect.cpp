#include "stdafx.h"
#include "Parry_Effect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CParry_Effect::CParry_Effect()
{
}


CParry_Effect::~CParry_Effect()
{
}

void CParry_Effect::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Player_Parry.bmp", L"Player_Parry");
	m_pFrameKey = L"Player_Parry";

	m_tInfo.fCX = 214.f;
	m_tInfo.fCY = 230.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 8;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = EFFECT;
}

int CParry_Effect::Update(void)
{
	Move_Frame(8);
	Update_Rect();

	if (m_tFrame.iFrameStart >= 8)
		return OBJ_DEAD;



	return OBJ_NOEVENT;
}

void CParry_Effect::Late_Update(void)
{
}

void CParry_Effect::Render(HDC hDC)
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

void CParry_Effect::Release(void)
{
}

#include "stdafx.h"
#include "Land_Effect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CLand_Effect::CLand_Effect()
{
}


CLand_Effect::~CLand_Effect()
{
}

void CLand_Effect::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/LandDust.bmp", L"LandDust");
	m_pFrameKey = L"LandDust";

	m_tInfo.fCX = 223.f;
	m_tInfo.fCY = 150.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 60;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = GAMEOBJECT;
}

int CLand_Effect::Update(void)
{
	Move_Frame(6);
	Update_Rect();

	if (m_tFrame.iFrameStart >= 6)
		return OBJ_DEAD;



	return OBJ_NOEVENT;
}

void CLand_Effect::Late_Update(void)
{
}

void CLand_Effect::Render(HDC hDC)
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

void CLand_Effect::Release(void)
{
}

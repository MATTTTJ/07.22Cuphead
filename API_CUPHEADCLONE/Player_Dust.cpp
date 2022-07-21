#include "stdafx.h"
#include "Player_Dust.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CPlayer_Dust::CPlayer_Dust()
{
}


CPlayer_Dust::~CPlayer_Dust()
{
}

void CPlayer_Dust::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/PlayerDust.bmp", L"PlayerDust");
	m_pFrameKey = L"PlayerDust";

	m_tInfo.fCX = 141.f;
	m_tInfo.fCY = 141.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 19;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = EFFECT;
}

int CPlayer_Dust::Update(void)
{
	Move_Frame(20);
	Update_Rect();

	if (m_tFrame.iFrameStart >= 20)
		return OBJ_DEAD;



	return OBJ_NOEVENT;
}

void CPlayer_Dust::Late_Update(void)
{
}

void CPlayer_Dust::Render(HDC hDC)
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

void CPlayer_Dust::Release(void)
{
}

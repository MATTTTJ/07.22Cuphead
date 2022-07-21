#include "stdafx.h"
#include "Dash_Effect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CDash_Effect::CDash_Effect()
{
}


CDash_Effect::~CDash_Effect()
{
}

void CDash_Effect::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/DashDust.bmp", L"DashDust");
	m_pFrameKey = L"DashDust";

	m_tInfo.fCX = 156.f;
	m_tInfo.fCY = 200.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 13;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 50;

	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = GAMEOBJECT;
}

int CDash_Effect::Update(void)
{
	Move_Frame(13);
	Update_Rect();

	if (m_tFrame.iFrameStart >= 13)
		return OBJ_DEAD;



	return OBJ_NOEVENT;
}

void CDash_Effect::Late_Update(void)
{
}

void CDash_Effect::Render(HDC hDC)
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

void CDash_Effect::Release(void)
{
}

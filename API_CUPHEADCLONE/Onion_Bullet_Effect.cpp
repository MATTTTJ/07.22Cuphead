#include "stdafx.h"
#include "Onion_Bullet_Effect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

COnion_Bullet_Effect::COnion_Bullet_Effect()
{
}


COnion_Bullet_Effect::~COnion_Bullet_Effect()
{
}

void COnion_Bullet_Effect::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Onion/Onion_Tears.bmp", L"Onion_Tears");

		m_pFrameKey = L"Onion_Tears";

	m_tInfo.fCX = 1365.f;
	m_tInfo.fCY = 407.f;


	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 300;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = EFFECT;
}

int COnion_Bullet_Effect::Update(void)
{
	Move_Frame();
	Update_Rect();

	if (m_tFrame.iFrameStart >= 3)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void COnion_Bullet_Effect::Late_Update(void)
{
}

void COnion_Bullet_Effect::Render(HDC hDC)
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
		RGB(255, 0, 255));	// ������ �ȼ��� ����
}

void COnion_Bullet_Effect::Release(void)
{
}

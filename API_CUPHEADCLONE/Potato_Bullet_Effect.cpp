#include "stdafx.h"
#include "Potato_Bullet_Effect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CPotato_Bullet_Effect::CPotato_Bullet_Effect()
{
}


CPotato_Bullet_Effect::~CPotato_Bullet_Effect()
{
}

void CPotato_Bullet_Effect::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Spit.bmp", L"Spit");
	m_pFrameKey = L"Spit";

	m_tInfo.fCX = 223.f;
	m_tInfo.fCY = 272.f;


	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = EFFECT;
}

int CPotato_Bullet_Effect::Update(void)
{
	Move_Frame(3);
	Update_Rect();

	if (m_tFrame.iFrameStart >= 3)
		return OBJ_DEAD;


	return OBJ_NOEVENT;
}

void CPotato_Bullet_Effect::Late_Update(void)
{
}

void CPotato_Bullet_Effect::Render(HDC hDC)
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

void CPotato_Bullet_Effect::Release(void)
{
}

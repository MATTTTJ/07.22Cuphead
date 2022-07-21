#include "stdafx.h"
#include "Bullet_Effect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CBullet_Effect::CBullet_Effect()
{
}


CBullet_Effect::~CBullet_Effect()
{
}

void CBullet_Effect::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Bullet/Circle/Circle_Birth_0.bmp", L"Bullet_Default_Birth");
	m_pFrameKey = L"Bullet_Default_Birth";

	m_tInfo.fCX = 140.f;
	m_tInfo.fCY = 140.f;

	/*m_tInfo.fCX = 280.f;
	m_tInfo.fCY = 280.f;*/

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = EFFECT;
}

int CBullet_Effect::Update(void)
{

	Move_Frame(4);
	Update_Rect();

	if (m_tFrame.iFrameStart >= 4)
		return OBJ_DEAD;



	return OBJ_NOEVENT;
}

void CBullet_Effect::Late_Update(void)
{
}

void CBullet_Effect::Render(HDC hDC)
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

void CBullet_Effect::Release(void)
{
}

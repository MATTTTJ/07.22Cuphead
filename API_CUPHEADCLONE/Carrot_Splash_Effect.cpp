#include "stdafx.h"
#include "Carrot_Splash_Effect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CCarrot_Splash_Effect::CCarrot_Splash_Effect()
{
}


CCarrot_Splash_Effect::~CCarrot_Splash_Effect()
{
}

void CCarrot_Splash_Effect::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Carrot/Carrot_Bullet_Destroy_2.bmp", L"Carrot_Bullet_Destroy");
	
	m_tInfo.fCX = 153.f;
	m_tInfo.fCY = 116.f;

	m_pFrameKey = L"Carrot_Bullet_Destroy";


	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = EFFECT;
}

int CCarrot_Splash_Effect::Update(void)
{
	Move_Frame(7);
	Update_Rect();

	if (m_tFrame.iFrameStart >= 7)
		return OBJ_DEAD;



	return OBJ_NOEVENT;
}

void CCarrot_Splash_Effect::Late_Update(void)
{
}

void CCarrot_Splash_Effect::Render(HDC hDC)
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

void CCarrot_Splash_Effect::Release(void)
{
}

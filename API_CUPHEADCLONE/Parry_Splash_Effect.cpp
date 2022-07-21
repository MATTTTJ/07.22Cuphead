#include "stdafx.h"
#include "Parry_Splash_Effect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CParry_Splash_Effect::CParry_Splash_Effect()
{
}


CParry_Splash_Effect::~CParry_Splash_Effect()
{
}

void CParry_Splash_Effect::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Onion/Onion_Proj_ParryableSplash.bmp", L"Onion_Proj_ParryableSplash");
	//m_pFrameKey = L"Onion_Proj_NonParryableASplash";

	m_tInfo.fCX = 202.f;
	m_tInfo.fCY = 126.f;

	m_pFrameKey = L"Onion_Proj_ParryableSplash";


	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = EFFECT;
}

int CParry_Splash_Effect::Update(void)
{
	Move_Frame(7);
	Update_Rect();

	if (m_tFrame.iFrameStart >= 7)
		return OBJ_DEAD;



	return OBJ_NOEVENT;
}

void CParry_Splash_Effect::Late_Update(void)
{
}

void CParry_Splash_Effect::Render(HDC hDC)
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

void CParry_Splash_Effect::Release(void)
{
}

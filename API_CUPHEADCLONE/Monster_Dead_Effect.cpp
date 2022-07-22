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
		m_tRect.left + iScrollX,	// 복사 받을 위치의 좌표 전달(x,y 순서)
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,		// 복사 받을 이미지의 길이 전달(가로, 세로순서)
		(int)m_tInfo.fCY,
		hMemDC,					// 비트맵을 가지고 있는 dc
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,						// 출력할 비트맵 시작 좌표(x,y 순서)
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,			// 복사 할 비트맵 의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(1, 1, 1));	// 제거할 픽셀의 색상
}

void CMonster_Dead_Effect::Release(void)
{
}

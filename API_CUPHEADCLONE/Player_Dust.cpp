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

void CPlayer_Dust::Release(void)
{
}

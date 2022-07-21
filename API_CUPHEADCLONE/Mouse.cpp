#include "stdafx.h"
#include "Mouse.h"


CMouse::CMouse()
{
}


CMouse::~CMouse()
{
}

void CMouse::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
}

int CMouse::Update(void)
{


	POINT	pt{};

	// 스크린 좌표 기준의 마우스 값을 얻어옴
	GetCursorPos(&pt);

	// 우리가 생성한 윈도우 창 기준으로 마우스 좌표를 보정
	ScreenToClient(g_hWnd, &pt);

	m_tInfo.fX = (float)pt.x;
	m_tInfo.fY = (float)pt.y;
	
	Update_Rect();

	ShowCursor(false);
	
	return OBJ_NOEVENT;
}

void CMouse::Late_Update(void)
{
	
}

void CMouse::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMouse::Release(void)
{
	
}

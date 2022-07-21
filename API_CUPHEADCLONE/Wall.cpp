#include "stdafx.h"
#include "Wall.h"
#include "ScrollMgr.h"

CWall::CWall()
{
}

CWall::CWall(POINT _pt)
{
	/*m_tInfo.fX = _pt.x;
	m_tInfo.fY = _pt.y;
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;*/
}

CWall::CWall(INFO _tInfo)
{
	//m_tInfo = _tInfo;
}


CWall::~CWall()
{

}

void CWall::Initialize(void)
{
	/*m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_fSpeed = 0.f;*/

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
	m_eRenderGroup = BACKGROUND;

}

int CWall::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CWall::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	/*if (m_bSelected)
	{
		HBRUSH MyBrush, OldBrush;
		MyBrush = CreateSolidBrush(RGB(12, 240, 243));
		OldBrush = (HBRUSH)::SelectObject(hDC, MyBrush);
		Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
		MyBrush = (HBRUSH)::SelectObject(hDC, OldBrush);
		DeleteObject(MyBrush);
	}
	else
	{*/
		//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	/*}*/
}

void CWall::Release(void)
{
}




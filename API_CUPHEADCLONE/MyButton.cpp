#include "stdafx.h"
#include "MyButton.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CMyButton::CMyButton()
{
}


CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize(void)
{
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 150.f;

	m_eRenderGroup = UI;
}

int CMyButton::Update(void)
{


	Update_Rect();

	return OBJ_NOEVENT;
}

void CMyButton::Late_Update(void)
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tRect, pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (!lstrcmp(L"Start", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGETUTORIAL);

			else if (!lstrcmp(L"Edit", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT);

			else if (!lstrcmp(L"Exit", m_pFrameKey))
				DestroyWindow(g_hWnd);

			return;
		}

		m_iDrawItv = 1;
	}
	else
		m_iDrawItv = 0;

}

void CMyButton::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left,								// 복사 받을 위치의 좌표 전달(x,y 순서)
		m_tRect.top,
		(int)m_tInfo.fCX,							// 복사 받을 이미지의 길이 전달(가로, 세로순서)
		(int)m_tInfo.fCY,
		hMemDC,										// 비트맵을 가지고 있는 dc
		int(m_tInfo.fCX) * m_iDrawItv,				// 출력할 비트맵 시작 좌표(x,y 순서)
		0,
		(int)m_tInfo.fCX,							// 복사 할 비트맵 의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));						// 제거할 픽셀의 색상
}

void CMyButton::Release(void)
{
	
}

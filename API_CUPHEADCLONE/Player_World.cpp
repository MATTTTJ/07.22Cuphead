#include "stdafx.h"
#include "Player_World.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CPlayer_World::CPlayer_World()
	:	m_eCurState(IDLE), m_ePreState(END), m_eLookState(LOOK_DOWN)
{
}


CPlayer_World::~CPlayer_World()
{
	Release();
}

void CPlayer_World::Initialize(void)
{
	m_tInfo = { 300.f, 300.f, 103.06f, 113.12f };
	m_HInfo = { 300.f, 300.f, 46.f, 65.f };
	m_fSpeed = 5.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Player_World/Player_World_0.bmp", L"Player_World");
	m_pFrameKey = L"Player_World";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iMotion = 5;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = GAMEOBJECT;
}

int CPlayer_World::Update(void)
{
	Key_Input();
	Offset();

	Motion_Change();
	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer_World::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			if (m_eLookState == LOOK_DOWN)
			{
				m_pFrameKey = L"Player_World";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 5;
				m_tFrame.dwFrameSpeed = 100;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			break;

		case WALK:
			if (m_eLookState == LOOK_LEFT)
			{
				m_pFrameKey = L"Player_Left";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 6;
				m_tFrame.iMotion = 8;
				m_tFrame.dwFrameSpeed = 100;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			else if (m_eLookState == LOOK_UP)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 15;
				m_tFrame.iMotion = 0;
				m_tFrame.dwFrameSpeed = 100;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			else if (m_eLookState == LOOK_RU)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 14;
				m_tFrame.iMotion = 3;
				m_tFrame.dwFrameSpeed = 100;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			else if (m_eLookState == LOOK_RIGHT)
			{
				m_tFrame.iFrameStart = 1;
				m_tFrame.iFrameEnd = 13;
				m_tFrame.iMotion = 3;
				m_tFrame.dwFrameSpeed = 100;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			else if (m_eLookState == LOOK_RD)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 15;
				m_tFrame.iMotion = 4;
				m_tFrame.dwFrameSpeed = 100;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			else if (m_eLookState == LOOK_DOWN)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 12;
				m_tFrame.iMotion = 6;
				m_tFrame.dwFrameSpeed = 100;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			/*else if (m_eLookState == LOOK_RIGHT)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 13;
				m_tFrame.iMotion = 3;
				m_tFrame.dwFrameSpeed = 100;
				m_tFrame.dwFrameTime = GetTickCount();
			}*/
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CPlayer_World::Late_Update(void)
{
	if (m_tRect.left <= 0)
		m_tRect.left = 0;

	if (m_tRect.top <= 0)
		m_tRect.top = 0;
}

void CPlayer_World::Render(HDC hDC)
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
		RGB(255, 0, 255));	// 제거할 픽셀의 색상

}

void CPlayer_World::Release(void)
{

}

void CPlayer_World::Offset(void)
{
	//int	iOffsetX = WINCX >> 1;

	int	iOffsetMinX = 300;
	int	iOffsetMaxX = 500;

	int	iOffsetMinY = 200;
	int	iOffsetMaxY = 400;

	int	iScrollX = int(CScrollMgr::Get_Instance()->Get_ScrollX());
	int	iScrollY = int(CScrollMgr::Get_Instance()->Get_ScrollY());

	// 플레이어가 중앙을 기준으로 왼쪽을 향하고 있음
	if (iOffsetMinX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	// 플레이어가 중앙을 기준으로 오른쪽을 향하고 있음
	if (iOffsetMaxX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	if (iOffsetMinY > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	// 플레이어가 중앙을 기준으로 오른쪽을 향하고 있음
	if (iOffsetMaxY < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
}

void CPlayer_World::Key_Input(void)
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		m_HInfo.fX += m_fSpeed;
		m_eCurState = WALK;
		m_eLookState = LOOK_RIGHT;

		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			/*m_tInfo.fX += m_fSpeed;
			m_HInfo.fX += m_fSpeed;
			m_tInfo.fY -= m_fSpeed;
			m_HInfo.fY -= m_fSpeed;*/
			m_tInfo.fX += cosf(45 * (PI / 180.f)) * m_fSpeed;
			m_tInfo.fY += sinf(45 * (PI / 180.f)) * m_fSpeed;

			m_eCurState = WALK;
			m_eLookState = LOOK_RU;
		}
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
	}

	else if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
	}


	else
		m_eCurState = IDLE;
}



#include "stdafx.h"
#include "Cloud_Birth.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Cloud.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Red_Cloud.h"
CCloud_Birth::CCloud_Birth()
{
}


CCloud_Birth::~CCloud_Birth()
{
}

void CCloud_Birth::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Taurus/Cloud_Birth.bmp", L"Cloud_Birth");
	m_pFrameKey = L"Cloud_Birth";

	m_tInfo.fCX = 141.f;
	m_tInfo.fCY = 141.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 13;
	m_tFrame.iMotion = 1;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = GAMEOBJECT;
}

int CCloud_Birth::Update(void)
{
	Move_Frame();
	Update_Rect();

	if (m_tFrame.iFrameStart >= 12)
	{
		if (rand() % 2 == 0)
			CObjMgr::Get_Instance()->Add_Object(OBJ_CLOUD, CAbstractFactory<CRed_Cloud>::Create(m_tInfo.fX, m_tInfo.fY));
		else
			CObjMgr::Get_Instance()->Add_Object(OBJ_CLOUD, CAbstractFactory<CCloud>::Create(m_tInfo.fX, m_tInfo.fY));
		
		return OBJ_DEAD;
	}



	return OBJ_NOEVENT;
}

void CCloud_Birth::Late_Update(void)
{
}

void CCloud_Birth::Render(HDC hDC)
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

void CCloud_Birth::Release(void)
{
}

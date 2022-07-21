#include "stdafx.h"
#include "Flower_Bullet_Dead.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CFlower_Bullet_Dead::CFlower_Bullet_Dead()
{
}


CFlower_Bullet_Dead::~CFlower_Bullet_Dead()
{
}

void CFlower_Bullet_Dead::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Enemy/Flower/Flower_Bullet_Dead.bmp", L"Flower_Bullet_Dead");

	m_pFrameKey = L"Flower_Bullet_Dead";

	m_tInfo.fCX = 110.f;
	m_tInfo.fCY = 110.f;


	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 9;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 70;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = EFFECT;
}

int CFlower_Bullet_Dead::Update(void)
{
	Move_Frame(9);
	Update_Rect();

	if (m_tFrame.iFrameStart >= 9)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CFlower_Bullet_Dead::Late_Update(void)
{
}

void CFlower_Bullet_Dead::Render(HDC hDC)
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
		RGB(31, 31, 31));	// 제거할 픽셀의 색상
}

void CFlower_Bullet_Dead::Release(void)
{
}

#include "stdafx.h"
#include "Cloud_Dead.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Cloud.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Red_Cloud.h"

CCloud_Dead::CCloud_Dead()
{
}


CCloud_Dead::~CCloud_Dead()
{
}

void CCloud_Dead::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Taurus/Cloud_Dead.bmp", L"Cloud_Dead");
	m_pFrameKey = L"Cloud_Dead";

	m_tInfo.fCX = 223.f;
	m_tInfo.fCY = 150.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 150;
	m_tFrame.dwFrameTime = GetTickCount();
	m_eRenderGroup = GAMEOBJECT;
}

int CCloud_Dead::Update(void)
{
	Move_Frame(6);
	Update_Rect();

	if (m_tFrame.iFrameStart >= 6)
		return OBJ_DEAD;



	return OBJ_NOEVENT;
}

void CCloud_Dead::Late_Update(void)
{
}

void CCloud_Dead::Render(HDC hDC)
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
		RGB(1, 1, 1));	// ������ �ȼ��� ����
}

void CCloud_Dead::Release(void)
{
}

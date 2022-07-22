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

void CCloud_Birth::Release(void)
{
}

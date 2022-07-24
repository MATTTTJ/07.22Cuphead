#include "stdafx.h"
#include "Star.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Cloud.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Cloud_Dead.h"
#include "DeadEventMgr.h"

CStar::CStar()
{
}


CStar::~CStar()
{
	Release();
}

void CStar::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Sagittarius/Star_BP.bmp", L"Star_BP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Sagittarius/Star_Dead.bmp", L"Star_Dead");
	
	m_pFrameKey = L"Star_BP";

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_HInfo.fCX = 40.f;
	m_HInfo.fCY = 40.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 12;
	m_tFrame.iMotion = 1;
	m_tFrame.dwFrameSpeed = 70;
	m_tFrame.dwFrameTime = GetTickCount();

	m_fDiagonal = 10.f;
	m_fSpeed = 2.5f;

	Update_Rect();

	m_eRenderGroup = GAMEOBJECT;
}

int CStar::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	//m_fAngle += m_fSpeed;

	//m_tInfo.fX += m_fDiagonal* cosf(m_fAngle * (PI / 180.f));
	//m_tInfo.fY -= m_fDiagonal* cosf(m_fAngle * (PI / 180.f));

	//m_HInfo.fX += m_fDiagonal * sinf(m_fAngle * (PI / 180.f));
	//m_HInfo.fY -= m_fDiagonal* cosf(m_fAngle * (PI / 180.f));
	m_tInfo.fX -= m_fSpeed;
	m_HInfo.fX -= m_fSpeed;

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CStar::Late_Update(void)
{
	
}

void CStar::Render(HDC hDC)
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
		RGB(255, 255, 255));	// ������ �ȼ��� ����

}

void CStar::Release(void)
{
}

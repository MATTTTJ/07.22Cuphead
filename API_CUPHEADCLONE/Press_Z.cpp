#include "stdafx.h"
#include "Press_Z.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "ObjTimer.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CPress_Z::CPress_Z()
{
}


CPress_Z::~CPress_Z()
{
	Release();
}

void CPress_Z::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Z.bmp", L"Z");
	m_pFrameKey = L"Z";

	m_tInfo.fCX = 42.f;
	m_tInfo.fCY = 52.f;


	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = UI;
}

int CPress_Z::Update(void)
{
	/*if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)->size())
	{
		pPlayer = CObjMgr::Get_Instance()->Get_Player();

		m_tStat = pPlayer->Get_PInfo();
	}
	if (m_tFrame.iFrameStart == 0)
		m_bDead = true;
	else*/
	if(m_bDead)
		return OBJ_DEAD;
	
	Move_Frame(0);
	Update_Info();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CPress_Z::Late_Update(void)
{
	if (CObjMgr::Get_Instance()->Get_Player()->Get_HInfo().fX < 900.f ||
		CObjMgr::Get_Instance()->Get_Player()->Get_HInfo().fX > 1100.f)
		m_bDead = true;
}

void CPress_Z::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,	// ���� ���� ��ġ�� ��ǥ ����(x,y ����)
		m_tRect.top+ iScrollY,
		(int)m_tInfo.fCX,		// ���� ���� �̹����� ���� ����(����, ���μ���)
		(int)m_tInfo.fCY,
		hMemDC,					// ��Ʈ���� ������ �ִ� dc
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,						// ����� ��Ʈ�� ���� ��ǥ(x,y ����)
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,			// ���� �� ��Ʈ�� �� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(1, 1, 1));	// ������ �ȼ��� ����
}

void CPress_Z::Release(void)
{
	///CObjMgr::Get_Instance()->Destroy_Instance();
}

void CPress_Z::Update_Info(void)
{
	m_tInfo.fX = CObjMgr::Get_Instance()->Get_Player()->Get_HInfo().fX;
	m_tInfo.fY = (float)CObjMgr::Get_Instance()->Get_Player()->Get_HRect().top;
}

#include "stdafx.h"
#include "Player_UI.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "ObjTimer.h"

CPlayer_UI::CPlayer_UI()
{
}


CPlayer_UI::~CPlayer_UI()
{
	Release();
}

void CPlayer_UI::Initialize(void)
{

	

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/UI/HP.bmp", L"HP");
	m_pFrameKey = L"HP";

	m_tInfo.fCX = 80.f;
	m_tInfo.fCY = 34.5f;

	Ani_Change_Timer.InitLoop(0.2f);

	m_tFrame.iFrameStart = 4;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 1;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = UI;
}

int CPlayer_UI::Update(void)
{
	/*if(!pPlayer)
	return OBJ_DEAD;*/

	if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)->size())
	{
		pPlayer = CObjMgr::Get_Instance()->Get_Player();

		m_tStat = pPlayer->Get_PInfo();
	}
	else
		return OBJ_DEAD;

	if (pPlayer != nullptr)
	{
		if (m_tStat.fHp == 8)
			m_tFrame.iFrameStart = 4;

		else if (m_tStat.fHp == 7)
			m_tFrame.iFrameStart = 3;

		else if (m_tStat.fHp == 6)
			m_tFrame.iFrameStart = 2;

		else if (m_tStat.fHp == 5)
			m_tFrame.iFrameStart = 1;

		else if (m_tStat.fHp == 4)
			m_tFrame.iFrameStart = 0;

		else if (m_tStat.fHp == 3)
		{
			m_tFrame.iMotion = 0;
			m_tFrame.iFrameStart = 5;
		}

		else if (m_tStat.fHp == 2)
		{
			m_tFrame.iFrameStart = 4;
		}

		else if (m_tStat.fHp == 1)  // && rand() % 2 == 1 )
		{
			if (Ani_Change_Timer.Check())
			{

				m_bIsRed = !m_bIsRed;

			}
			if (!m_bIsRed)
			{
				m_tFrame.iMotion = 0;
				m_tFrame.iFrameStart = 3;
				//m_bIsRed = !m_bIsRed;
			}
			else
			{
				m_tFrame.iMotion = 0;
				m_tFrame.iFrameStart = 2;
				//m_bIsRed = !m_bIsRed;
			}
		}
		else if (m_tStat.fHp == 0)
		{
			m_tFrame.iMotion = 0;
			m_tFrame.iFrameStart = 0;	
		}
	}
	
	
	
	//Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CPlayer_UI::Late_Update(void)
{
}

void CPlayer_UI::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		m_tRect.left ,	// ���� ���� ��ġ�� ��ǥ ����(x,y ����)
		m_tRect.top ,
		(int)m_tInfo.fCX,		// ���� ���� �̹����� ���� ����(����, ���μ���)
		(int)m_tInfo.fCY,
		hMemDC,					// ��Ʈ���� ������ �ִ� dc
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,						// ����� ��Ʈ�� ���� ��ǥ(x,y ����)
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,			// ���� �� ��Ʈ�� �� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(1, 1, 1));	// ������ �ȼ��� ����
}

void CPlayer_UI::Release(void)
{
}

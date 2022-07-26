#include "stdafx.h"
#include "Cloud.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Cloud.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Cloud_Dead.h"
#include "DeadEventMgr.h"
#include "SoundMgr.h"
CCloud::CCloud()
{
}


CCloud::~CCloud()
{
	Release();
}

void CCloud::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Taurus/Cloud.bmp", L"Cloud");
	m_pFrameKey = L"Cloud";

	m_tInfo.fCX = 344.f;
	m_tInfo.fCY = 186.f;

	m_HInfo.fCX = 344.f;
	m_HInfo.fCY = 186.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();


	Update_Rect();

	CLOUDPOINT	tCloudLinePt[2] = {
		{ (float)m_HRect.left , m_HInfo.fY - 1.f },
		{ (float)m_HRect.right, m_HInfo.fY - 1.f }
	};


	CLineMgr::Get_Instance()->Get_LineList()->push_back(new CLine(tCloudLinePt[0], tCloudLinePt[1]));


	m_eRenderGroup = BOSSSTAGE;
}

int CCloud::Update(void)
{
	Move_Frame();
	Update_Rect();

	
	if (m_bDead)
	{
		if(GetTickCount() % 2 == 0)
		CSoundMgr::Get_Instance()->PlaySound(L"Boss_thunder1.wav", SOUND_EFFECT, 1.f);
		else if(GetTickCount() % 2 == 1)
		CSoundMgr::Get_Instance()->PlaySound(L"Boss_thunder2.wav", SOUND_EFFECT, 1.f);

		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CCloud_Dead>::Create(m_tInfo.fX, m_tInfo.fY));
		CDeadEventMgr::Get_Instance()->broadcast(this);
		return OBJ_DEAD;
	}

	

	return OBJ_NOEVENT;
}

void CCloud::Late_Update(void)
{
}

void CCloud::Render(HDC hDC)
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

void CCloud::Release(void)
{
	CLOUDPOINT	tCloudLinePt[2] = {
		{ (float)m_HRect.left , m_HInfo.fY - 1.f },
		{ (float)m_HRect.right, m_HInfo.fY - 1.f }

	};
	CLineMgr::Get_Instance()->Delete_Line_Cloud(CLine(tCloudLinePt[0], tCloudLinePt[1]));
}

void CCloud::Creat_Line_Cloud(void)
{//리스트에 안들어가고 뻑남 
	/*CLOUDPOINT	tCloudLinePt[2] = {
		{ (float)m_HRect.left , m_HInfo.fY },
		{ (float)m_HRect.right, m_HInfo.fY }
	};

	m_pLineList->push_back(new CLine(tCloudLinePt[0], tCloudLinePt[1]));*/
}



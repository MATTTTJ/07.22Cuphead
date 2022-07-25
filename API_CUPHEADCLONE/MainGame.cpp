#include "stdafx.h"
#include "MainGame.h"

#include "ObjMgr.h"

#include "AbstractFactory.h"
#include "Player.h"

#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

#include "SceneMgr.h"

#include "SoundMgr.h"

CMainGame::CMainGame()
	: m_dwTime(GetTickCount()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);
	srand(unsigned(time(NULL)));

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Back/BackGround.bmp", L"Back");
	CSoundMgr::Get_Instance()->Initialize();
	CSceneMgr::Get_Instance()->Scene_Change(SC_STAGESECOND);

#ifdef _DEBUG

	if (::AllocConsole() == TRUE)
	{
		FILE* nfp[3];
		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}

#endif
	
}



void CMainGame::Update(void)
{
	CSceneMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Update();

	if (CKeyMgr::Get_Instance()->Key_Down('1'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGEWORLD);
	}

	else if (CKeyMgr::Get_Instance()->Key_Down('2'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGETUTORIAL);
	}

	else if (CKeyMgr::Get_Instance()->Key_Down('3'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGEROOT);
	}

	else if (CKeyMgr::Get_Instance()->Key_Down('4'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGEFIRST);
	}

	else if (CKeyMgr::Get_Instance()->Key_Down('5'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGESECOND);
	}
}

void CMainGame::Late_Update(void)
{
	CSceneMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();
}

void CMainGame::Render(void)
{
	// fps

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

	if (SC_LOGO == CSceneMgr::Get_Instance()->Get_SceneID())
		return;

	
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hMemDC,0,	0,	SRCCOPY);
	
	CSceneMgr::Get_Instance()->Render(hMemDC);

}

void CMainGame::Release(void)
{
#ifdef _DEBUG
/*
	FreeConsole();*/

#endif // _DEBUG

	/*CTileMgr::Get_Instance()->Destroy_Instance();*/
	CSceneMgr::Get_Instance()->Destroy_Instance();
	CBmpMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CLineMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();
	CSoundMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
}

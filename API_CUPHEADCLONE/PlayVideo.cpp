#include "stdafx.h"
#include "PlayVideo.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"


CPlayVideo::CPlayVideo()
{
}


CPlayVideo::~CPlayVideo()
{
	Release();
}

void CPlayVideo::Initialize(void)
{
	
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Back/BackGround.bmp", L"Back");
	
	//BMP �Ŵ����� �����߸� ����ϰ� ����, �ٵ� ����� ���� ���� �ȳ���
	//CBmpMgr::Get_Instance()->Release();
	
	
	// MCIWndCreate : ��Ƽ�̵� ����ϱ� ���� â�� �����ϴ� �Լ�
	// MCIWndCreate(�θ� �ڵ�, mci�����츦 ����ϴ� �ν��Ͻ� �ڵ�, ������ ���(�ڽ� â�� ���� | �� ��� ��� | �÷��̹� ������ ����), ����� ������ ���)
	m_hVideo = MCIWndCreate(g_hWnd, nullptr, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, L"../Resource/Video/Intro.wmv");
	//CSoundMgr::Get_Instance()->PlayBGM(L"Stage_First.wav", 0.6f);

	CSoundMgr::Get_Instance()->PlaySound(L"Intro_audio.wav",SOUND_INTRO, 1.f);
	// MoveWindow : �������� ����� ũ�⸦ ����

	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);
	MCIWndPlay(m_hVideo);
	

	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/Logo.bmp", L"Logo");
}

int CPlayVideo::Update(void)
{
	return 0;
}

void CPlayVideo::Late_Update(void)
{
	if (MCIWndGetLength(m_hVideo) <= MCIWndGetPosition(m_hVideo) ||
		CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Title/Title_Screen_Background.bmp", L"Menu");
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		return;
	}
}

void CPlayVideo::Render(HDC hDC)
{
//	HDC	hVDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
//	BitBlt(hVDC, 0, 0, WINCX, WINCY, hVDC, 0, 0, SRCCOPY);
	//CSceneMgr::Get_Instance()->Render(hVDC);

}

void CPlayVideo::Release(void)
{
	MCIWndClose(m_hVideo);
}

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
	// MCIWndCreate : 멀티미디어를 재생하기 위한 창을 생성하는 함수
	// MCIWndCreate(부모 핸들, mci윈도우를 사용하는 인스턴스 핸들, 윈도우 모양(자식 창의 형태 | 그 즉시 출력 | 플레이바 생성을 안함), 재생할 파일의 경로)
	m_hVideo = MCIWndCreate(g_hWnd, nullptr, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, L"../Video/Wildlife.wmv");

	// MoveWindow : 동영상을 재생할 크기를 설정

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
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		return;
	}
}

void CPlayVideo::Render(HDC hDC)
{
}

void CPlayVideo::Release(void)
{
	MCIWndClose(m_hVideo);
}

#include "stdafx.h"
#include "PlayOutro.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CPlayOutro::CPlayOutro()
{
}


CPlayOutro::~CPlayOutro()
{
	Release();
}

void CPlayOutro::Initialize(void)
{
	// MCIWndCreate : 멀티미디어를 재생하기 위한 창을 생성하는 함수
	// MCIWndCreate(부모 핸들, mci윈도우를 사용하는 인스턴스 핸들, 윈도우 모양(자식 창의 형태 | 그 즉시 출력 | 플레이바 생성을 안함), 재생할 파일의 경로)
	m_hVideo = MCIWndCreate(g_hWnd, nullptr, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, L"../Resource/Video/Outro.wmv");
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlaySound(L"Ourtro_audio.wav", SOUND_OUTRO, 1.f);
	CSoundMgr::Get_Instance()->PlaySound(L"sfx_level_genie_voice_laugh_02.wav", SOUND_EFFECT, 1.f);

	// MoveWindow : 동영상을 재생할 크기를 설정

	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);
	MCIWndPlay(m_hVideo);

	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/Logo.bmp", L"Logo");
}

int CPlayOutro::Update(void)
{
	return 0;
}

void CPlayOutro::Late_Update(void)
{
	if (MCIWndGetLength(m_hVideo) <= MCIWndGetPosition(m_hVideo) ||
		CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		PostQuitMessage(0);
		return;
	}
}

void CPlayOutro::Render(HDC hDC)
{
}

void CPlayOutro::Release(void)
{
	MCIWndClose(m_hVideo);
}

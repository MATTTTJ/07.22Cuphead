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
	// MCIWndCreate : ��Ƽ�̵� ����ϱ� ���� â�� �����ϴ� �Լ�
	// MCIWndCreate(�θ� �ڵ�, mci�����츦 ����ϴ� �ν��Ͻ� �ڵ�, ������ ���(�ڽ� â�� ���� | �� ��� ��� | �÷��̹� ������ ����), ����� ������ ���)
	m_hVideo = MCIWndCreate(g_hWnd, nullptr, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, L"../Resource/Video/Outro.wmv");

	// MoveWindow : �������� ����� ũ�⸦ ����

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

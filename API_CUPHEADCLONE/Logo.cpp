#include "stdafx.h"
#include "Logo.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CLogo::CLogo()
{
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize(void)
{
	// MCIWndCreate : ��Ƽ�̵� ����ϱ� ���� â�� �����ϴ� �Լ�
	// MCIWndCreate(�θ� �ڵ�, mci�����츦 ����ϴ� �ν��Ͻ� �ڵ�, ������ ���(�ڽ� â�� ���� | �� ��� ��� | �÷��̹� ������ ����), ����� ������ ���)
	/*m_hVideo = MCIWndCreate(g_hWnd, nullptr, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, L"../Video/Wildlife.wmv");*/

	// MoveWindow : �������� ����� ũ�⸦ ����

	//MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);
	//MCIWndPlay(m_hVideo);

	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/Logo.bmp", L"Logo");
}

int CLogo::Update(void)
{

	return 0;
}

void CLogo::Late_Update(void)
{
	//if (MCIWndGetLength(m_hVideo) <= MCIWndGetPosition(m_hVideo) ||
	//	CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	//{
	//	CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
	//	return;
	//}


}

void CLogo::Render(HDC hDC)
{
	//HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Logo");

	//BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void CLogo::Release(void)
{
	MCIWndClose(m_hVideo);
}

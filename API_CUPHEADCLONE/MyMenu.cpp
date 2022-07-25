#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize(void)
{
	/*CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Button/Start.bmp", L"Start");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Button/Edit.bmp", L"Edit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Button/Exit.bmp", L"Exit");*/

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Title/Title_Screen_Background.bmp", L"Menu");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Title/title_cuphead_1.bmp", L"title_cuphead");
	CSoundMgr::Get_Instance()->PlayBGM(L"bgm_title_screen.wav", SOUND_BGM);

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 32;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CMyMenu::Update(void)
{
	//CObjMgr::Get_Instance()->Update();
	Move_Frame();
	return 0;
}

void CMyMenu::Late_Update(void)
{
	//CObjMgr::Get_Instance()->Late_Update();
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGEFIRST);
		return;
	}
}

void CMyMenu::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Menu");
	HDC	hLoopDC = CBmpMgr::Get_Instance()->Find_Img(L"title_cuphead");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	GdiTransparentBlt(hDC,
		240,	// ���� ���� ��ġ�� ��ǥ ����(x,y ����)
		0,
		760,		// ���� ���� �̹����� ���� ����(����, ���μ���)
		WINCY,
		hLoopDC,					// ��Ʈ���� ������ �ִ� dc
		(int)800 * m_tFrame.iFrameStart,  // ����� ��Ʈ�� ���� ��ǥ(x,y ����)
		(int)WINCY * m_tFrame.iMotion,
		760,// ���� �� ��Ʈ�� �� ����, ���� ������
		800,
		RGB(127, 127, 127));	// ������ �ȼ��� ����



	
//	CObjMgr::Get_Instance()->Render(hDC);
}

void CMyMenu::Release(void)
{
	//CObjMgr::Get_Instance()->Delete_OBJID(OBJ_BUTTON);
	CSoundMgr::Get_Instance()->StopAll();
}

void CMyMenu::Move_Frame(void)
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		m_tFrame.iFrameStart++;

		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}

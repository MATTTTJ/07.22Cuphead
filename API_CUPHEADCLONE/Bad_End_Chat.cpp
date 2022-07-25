#include "stdafx.h"
#include "Bad_End_Chat.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"

CBad_End_Chat::CBad_End_Chat()
{
}


CBad_End_Chat::~CBad_End_Chat()
{
	Release();
}

void CBad_End_Chat::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/BadEnd/BadEnd_Chat.bmp", L"BadEnd_Chat");
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 3000;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CBad_End_Chat::Update(void)
{
	Move_Frame();

	if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
	{
		//CSceneMgr::Get_Instance()->Scene_Change(SC_VIDEO);
		//return;
	}
	return 0;
}

void CBad_End_Chat::Late_Update(void)
{
}

void CBad_End_Chat::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"BadEnd_Chat");
	GdiTransparentBlt(hDC,
		0,	// ���� ���� ��ġ�� ��ǥ ����(x,y ����)
		0,
		WINCX,		// ���� ���� �̹����� ���� ����(����, ���μ���)
		WINCY,
		hMemDC,					// ��Ʈ���� ������ �ִ� dc
		(int)WINCX * m_tFrame.iFrameStart,  // ����� ��Ʈ�� ���� ��ǥ(x,y ����)
		(int)WINCY * m_tFrame.iMotion,
		WINCX,// ���� �� ��Ʈ�� �� ����, ���� ������
		WINCY,
		RGB(127, 127, 127));	// ������ �ȼ��� ����
}

void CBad_End_Chat::Release(void)
{
	
}

void CBad_End_Chat::Move_Frame(void)
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		m_tFrame.iFrameStart++;

		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}
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

	CSoundMgr::Get_Instance()->PlaySound(L"Intro_devil_audio_1.wav", SOUND_MONSTER, 1.f);

}

int CBad_End_Chat::Update(void)
{
	Move_Frame();
	return 0;
}

void CBad_End_Chat::Late_Update(void)
{
	if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_INTRO);
		return;
	}
}

void CBad_End_Chat::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"BadEnd_Chat");

	GdiTransparentBlt(hDC,
		0,	// 복사 받을 위치의 좌표 전달(x,y 순서)
		0,
		WINCX,		// 복사 받을 이미지의 길이 전달(가로, 세로순서)
		WINCY,
		hMemDC,					// 비트맵을 가지고 있는 dc
		(int)WINCX * m_tFrame.iFrameStart,  // 출력할 비트맵 시작 좌표(x,y 순서)
		(int)WINCY * m_tFrame.iMotion,
		WINCX,// 복사 할 비트맵 의 가로, 세로 사이즈
		WINCY,
		RGB(127, 127, 127));	// 제거할 픽셀의 색상
}

void CBad_End_Chat::Release(void)
{
	//CBmpMgr::Get_Instance()->Release();
	//CObjMgr::Get_Instance()->Destroy_Instance();
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

#include "stdafx.h"
#include "Stage_End.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
CStage_End::CStage_End()
{
}


CStage_End::~CStage_End()
{
}

void CStage_End::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/BadEnd/BadEnd_All.bmp", L"BadEnd_All");
	CSoundMgr::Get_Instance()->PlayBGM(L"devil_fire_hell.wav", SOUND_BGM);
	//CSoundMgr::Get_Instance()->PlaySound(L"sfx_level_genie_voice_laugh_02.wav", SOUND_EFFECT, 1.f);

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 300;
	m_tFrame.dwFrameTime = GetTickCount();

	m_dwEndTime = GetTickCount();
}

int CStage_End::Update(void)
{
	Move_Frame();

	if (m_dwEndTime + 6000 < GetTickCount())
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_OUTRO);
	}
	return 0;
}

void CStage_End::Late_Update(void)
{

}

void CStage_End::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"BadEnd_All");

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

void CStage_End::Release(void)
{
}

void CStage_End::Move_Frame(void)
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		m_tFrame.iFrameStart++;

		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}

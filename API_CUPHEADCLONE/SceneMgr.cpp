#include "stdafx.h"
#include "SceneMgr.h"
#include "Tutorial_Stage.h"
#include "Root_Stage.h"
#include "World_Stage.h"
#include "First_Stage.h"
#include "Second_Stage.h"
#include "Stage_End.h"
#include "Bad_End_Chat.h"
#include "PlayVideo.h"
CSceneMgr*		CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_ePreScene(SC_END), m_eCurScene(SC_STAGEWORLD)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SC_LOGO:
			m_pScene = new CLogo;
			break;

		case SC_MENU:
			m_pScene = new CMyMenu;
			break;

		case SC_STAGEWORLD:
			m_pScene = new CWorld_Stage;
			break;

		case SC_STAGETUTORIAL:
			m_pScene = new CTutorial_Stage;
			break;

		case SC_STAGEROOT:
			m_pScene = new CRoot_Stage;
			break;

		case SC_STAGEFIRST:
			m_pScene = new CFirst_Stage;
			break;

		case SC_STAGESECOND:
			m_pScene = new CSecond_Stage;
			break;
		case SC_STAGEEND:
			m_pScene = new CStage_End;
			break;
		case SC_BADENDCHAT:
			m_pScene = new CBad_End_Chat;
			break;
		case SC_INTRO:
			m_pScene = new CPlayVideo;
			break;

		}

		m_pScene->Initialize();
		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::Update(void)
{
	if (m_pScene)
		m_pScene->Update();


}

void CSceneMgr::Late_Update(void)
{
	if (m_pScene)
		m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	if (m_pScene)
		m_pScene->Render(hDC);
}

void CSceneMgr::Release(void)
{
	Safe_Delete<CScene*>(m_pScene);
}

#include "stdafx.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"

CScrollMgr*	CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
	: m_fScrollX(0.f), m_fScrollY(0.f)
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock(void)
{
	m_eCurScene = CSceneMgr::Get_Instance()->Get_SceneID();

	switch (m_eCurScene)
	{
	//case SC_LOGO:
	//	break;
	//case SC_MENU:
	//	break;
	//case SC_EDIT:
	//	break;
	//case SC_STAGEWORLD:
	//	break;
	/*case SC_STAGETUTORIAL:
		break;*/
	case SC_STAGEROOT:
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (WINCX - STAGE_ROOT_CX > m_fScrollX)
			m_fScrollX = WINCX - STAGE_ROOT_CX;

		if (WINCY - STAGE_ROOT_CY > m_fScrollY)
			m_fScrollY = WINCY - STAGE_ROOT_CY;
		break;

	case SC_STAGEFIRST:
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (WINCX - STAGE_FIRST_CX > m_fScrollX)
			m_fScrollX = WINCX - STAGE_FIRST_CX;

		if (WINCY - STAGE_FIRST_CY > m_fScrollY)
			m_fScrollY = WINCY - STAGE_FIRST_CY;
		break;

	case SC_STAGESECOND:
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (WINCX - STAGE_SECOND_CX > m_fScrollX)
			m_fScrollX = WINCX - STAGE_SECOND_CX;

		if (WINCY - STAGE_SECOND_CY > m_fScrollY)
			m_fScrollY = WINCY - STAGE_SECOND_CY;
		break;

	case SC_STAGEBOSS_2:
		break;
	case SC_END:
		break;
	default:
		break;
	}
}

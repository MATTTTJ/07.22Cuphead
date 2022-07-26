#include "stdafx.h"
#include "Carrot.h"
#include "ObjMgr.h"
#include "Bullet_Effect.h"
#include "EffectMgr.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Carrot_Bullet.h"
#include "Carrot_Splash_Effect.h"
#include "Carrot_Beam.h"
#include "SceneMgr.h"
#include "Monster_Dead_Effect.h"


CCarrot::CCarrot()
	:m_eCurState(INTRO_EARTH), m_ePreState(INTRO_EARTH)
{
}


CCarrot::~CCarrot()
{
	Release();
}

void CCarrot::Initialize(void)
{
	m_tInfo = { 950.f, 350.f, 557.f, 461.f };
	m_HInfo = { 950.f, 350.f, 262.f, 350.f };

	m_fHp = 30.f;

	////When the Potato Bullet Create
	ShootTimer.InitLoop(2.5f);
	////The Potato Bullet Distance 
	ShootCoolTimer.InitLoop(0.8f);


	//Beam_State
	BeamStateTimer.InitLoop(7.9f);
	BeamStateCoolTimer.InitLoop(3.6f);
	//Beam_Shoot
	BeamTimer.InitLoop(7.9f);
	BeamCoolTimer.InitLoop(0.2f);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Carrot/Carrot_Intro_Earth.bmp", L"Carrot_Intro_Earth");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Carrot/Carrot_Intro.bmp", L"Carrot_Intro");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Carrot/Carrot_Attack.bmp", L"Carrot_Attack");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Carrot/Carrot_Beam.bmp", L"Carrot_Beam");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Carrot/Carrot_Death.bmp", L"Carrot_Death");
	CSoundMgr::Get_Instance()->PlaySound(L"veggies_Carrot_Rise.wav", SOUND_MONSTER, 0.6f);


	m_pFrameKey = L"Carrot_Intro_Earth";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 17;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 70;
	m_tFrame.dwFrameTime = GetTickCount();
	m_dwTimer = GetTickCount();

	m_bIsIntro_First = true;

	m_iShootFrameCnt = 22;
	m_iShootFrameMaxCnt = 21;
	m_iBeamCnt = 0;
	m_iBeamMaxCnt = 6;

	m_eRenderGroup = GAMEOBJECT;
}

int CCarrot::Update(void)
{
	if (m_bDead)
	{
		//Sleep(140);
		m_eCurState = DEAD;
		if (m_tFrame.iFrameStart == 0)
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonster_Dead_Effect>::Create(m_tInfo.fX + (rand() % 300), m_tInfo.fY + (rand() % 300)));
		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_MONSTER);
			return OBJ_DEAD;
		}
	}


	Carrot_Intro();
	Carrot_Intro_Earth();


	Update_Controller();

	Motion_Change();
	Move_Frame();


	Update_Rect();

	return OBJ_NOEVENT;
}

void CCarrot::Late_Update(void)
{
}

void CCarrot::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,	// 복사 받을 위치의 좌표 전달(x,y 순서)
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,		// 복사 받을 이미지의 길이 전달(가로, 세로순서)
		(int)m_tInfo.fCY,
		hMemDC,					// 비트맵을 가지고 있는 dc
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,						// 출력할 비트맵 시작 좌표(x,y 순서)
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,			// 복사 할 비트맵 의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));	// 제거할 픽셀의 색상


							//Rectangle(hDC, m_HRect.left + iScrollX, m_HRect.top + iScrollY, m_HRect.right + iScrollX, m_HRect.bottom + iScrollY);
}

void CCarrot::Release(void)
{
}

void CCarrot::Collision_Event(CObj * _OtherObj, float fColX, float fColY)
{
	CBullet*	pBullet = dynamic_cast<CBullet*>(_OtherObj);
	if (pBullet)
	{
		if (pBullet->Get_Dead()) return;

		m_fHp -= pBullet->Get_Damage();

	}

	if (m_fHp <= EPSILON)
	{
		//CSoundMgr::Get_Instance()->StopSound(SOUND_MONSTER);
		CSoundMgr::Get_Instance()->PlaySound(L"veggies_Carrot_Die.wav", SOUND_INTRO, 0.6f);

		m_bDead = true;
	}
}

void CCarrot::Update_Controller()
{
	if (m_bDead) return;
	//Carrot_Bullet_Control
	if (ShootTimer.Check()) //BEAM
	{
		m_bShootState = !m_bShootState;
	}


	if (m_bShootState && ShootCoolTimer.Check())
	{
		//m_eCurState = BEAM;
		//m_eCurState = ATTACK;
		/*if (m_iShootCnt >= m_iShootMaxCnt)
			m_eCurState = ATTACK;*/
		m_iShootFrameCnt = 0;
	}



	if (m_iShootFrameCnt <= m_iShootFrameMaxCnt)
	{
		if (m_iShootFrameCnt == m_iShootFrameMaxCnt)
		{
			CObj* pCarrot = CAbstractFactory<CCarrot_Bullet>::Create((float)(rand() % WINCX), -100, DIR_DOWN);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, pCarrot);
			//CObj* pCarrot_Effect = CAbstractFactory<CCarrot_Bullet_Effect>::Create(m_HInfo.fX - 180, m_HInfo.fY + 100);
			//CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, pPotato_Effect);

			m_bIsBeamStart = true;
		}
		m_iShootFrameCnt++;

	}

	if (m_bIsBeamStart && BeamStateTimer.Check())
	{
		m_bBeamState = !m_bBeamState;
	}

	if (m_bBeamState && BeamStateCoolTimer.Check())
	{
		m_eCurState = BEAM;
		CSoundMgr::Get_Instance()->PlaySound(L"veggies_Carrot_MindMeld_Loop.wav", SOUND_MONSTER, 0.6f);
		if (m_iBeamCnt >= m_iBeamMaxCnt)
		{
			m_eCurState = ATTACK;
			CSoundMgr::Get_Instance()->StopSound(SOUND_MONSTER);
		}
	}

	if (BeamTimer.Check() && !m_bBeam_Attack)
	{
		m_bBeam_Start = !m_bBeam_Start;
		m_iBeamCnt = 0;

	}

	if (m_bBeam_Start && BeamCoolTimer.Check())
	{
		if (m_iBeamCnt < m_iBeamMaxCnt)
		{
			if (m_dwTimer + 5 < GetTickCount())
			{
				CObj* pBeam = CAbstractFactory<CCarrot_Beam>::Create(m_HInfo.fX, m_HInfo.fY);
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, pBeam);
				/*if (GetTickCount() % 2 == 0)
				CSoundMgr::Get_Instance()->StopSound(SOUND_MONSTER);

				else if (GetTickCount() % 2 == 0)
					CSoundMgr::Get_Instance()->PlaySound(L"veggies_Carrot_MindMeld_Loop.wav", SOUND_MONSTER, 0.6f);*/
			}

		}
		m_iBeamCnt++;
		m_dwTimer = GetTickCount();
	}
	/*if (m_iBeamCnt >= m_iBeamMaxCnt)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_MONSTER);
	}*/
}

// Beam_Control


void CCarrot::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case INTRO_EARTH:
			m_pFrameKey = L"Carrot_Intro_Earth";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 17;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case INTRO:
			m_tInfo.fCX = 592.f;
			m_tInfo.fCY = 549.f;
			m_pFrameKey = L"Carrot_Intro";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 24;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 70;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		case ATTACK:
			m_tInfo.fCX = 466.f;
			m_tInfo.fCY = 501.f;
			m_pFrameKey = L"Carrot_Attack";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 21;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 35;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case BEAM:
			m_tInfo.fCX = 458.f;
			m_tInfo.fCY = 522.f;
			m_pFrameKey = L"Carrot_Beam";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case DEAD:
			m_tInfo.fCX = 323.f;
			m_tInfo.fCY = 456.f;
			m_pFrameKey = L"Carrot_Death";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CCarrot::Carrot_Intro_Earth(void)
{
	if (m_bIsIntro_First)
	{

		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			m_eCurState = INTRO;

			if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
			{
				m_bIsIntro_Second = true;
				m_bIsIntro_First = false;
			}
		}
	}
}

void CCarrot::Carrot_Intro(void)
{
	if (m_bIsIntro_Second == false) return;

	else if (m_bIsIntro_Second)
	{
		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			m_eCurState = ATTACK;
			m_bIsIntro_Second = false;
		}
	}
}

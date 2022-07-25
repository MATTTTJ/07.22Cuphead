#include "stdafx.h"
#include "Sagittarius.h"
#include "ObjMgr.h"
#include "Bullet_Effect.h"
#include "EffectMgr.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Arrow.h"
#include "Star.h"
#include "Player_Dust.h"
#include "BasicBullet.h"
#include "BigCloud.h"


CSagittarius::CSagittarius()
	: m_eCurState(INTRO_STAR), m_ePreState(INTRO_STAR)
{
}


CSagittarius::~CSagittarius()
{
	Release();
}

void CSagittarius::Initialize(void)
{
	m_tInfo.fCX = 1000.f;
	m_tInfo.fCY = 1000.f;

	m_HInfo.fCX = 100.f;
	m_HInfo.fCY = 200.f;


	m_fMaxHp = 10.f;

	m_fHp = m_fMaxHp;

	//When the Potato Bullet Create
	ShootTimer.InitLoop(10.f);
	//The Potato Bullet Distance 
	ShootCoolTimer.InitLoop(1.f);

	ShootStateTimer.InitLoop(5.1f);
	ShootStateCoolTimer.InitLoop(1.13f);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Sagittarius/Sagittarius_Intro.bmp", L"Sagittarius_Intro");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Sagittarius/Sagittarius_Idle.bmp", L"Sagittarius_Idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Sagittarius/Sagittarius_Attack_0.bmp", L"Sagittarius_Attack");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Sagittarius/Taurus_Attack.bmp", L"Taurus_Attack");

	m_fDiagonal = 10.f;
	m_fSpeed = 2.5f;



	m_pFrameKey = L"Sagittarius_Intro";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_dwTimer = GetTickCount();

	m_bIsIntro_First = true;
	m_iShootFrameCnt = 8;
	m_iShootFrameMaxCnt = 7;
	m_iShootCnt = 0;
	m_iShootMaxCnt = 4;

	m_dwStarCoolTime = GetTickCount();

	m_bFisrtTime = true;

	m_bPhaseOne = true;
	m_bPhaseTwo = false;
	m_bPhaseThree = false;

	m_iStarCnt = 0;
	m_iStarMaxCnt = 10;

	m_eRenderGroup = GAMEOBJECT;
}

int CSagittarius::Update(void)
{
	if (m_bDead)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBigCloud>::Create(m_tInfo.fX, m_tInfo.fY));
		return OBJ_DEAD;
	}


	Sagittarius_Intro();
	Sagittarius_Intro_Star();

	if (m_bPhaseOne && !m_bPhaseTwo && !m_bPhaseThree)
	{
		if (m_eCurState == IDLE || m_eCurState == ATTACK)
		{
			m_fAngle += m_fSpeed;

			float fOrgAngle = m_fAngle;

			m_tInfo.fX += m_fDiagonal * cosf(m_fAngle * (PI / 360.f));  //sinf(m_fAngle * (PI / 270.f));
			m_tInfo.fY -= m_fDiagonal * sinf(m_fAngle * (PI / 270.f)); // cosf(m_fAngle * (PI / 360.f));

			m_HInfo.fX += m_fDiagonal * cosf(m_fAngle * (PI / 360.f));
			m_HInfo.fY -= m_fDiagonal * sinf(m_fAngle * (PI / 270.f));

			if (m_dwDustTime + 100 < GetTickCount())
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayer_Dust>::Create((float)m_HRect.right - 50.f, m_tInfo.fY + 150.f));
				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayer_Dust>::Create((float)m_HRect.right + 30.f, m_tInfo.fY + 100.f));
				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayer_Dust>::Create((float)m_HRect.right - 10.f, m_tInfo.fY + 125.f));
				m_dwDustTime = GetTickCount();
			}
		}
	}

	Check_PhaseTwo();

	if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_PARRY)->size() == 0 && m_bPhaseTwo && m_iStarCnt == 10)
	{
		m_bPhaseThree = true;
		m_bPhaseOne = false;
		m_bPhaseTwo = false;
		m_HInfo.fCX = 100.f;
		m_HInfo.fCY = 200.f;
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBigCloud>::Create(m_tInfo.fX, m_tInfo.fY));
	}

	if (m_bPhaseThree && !m_bPhaseOne && !m_bPhaseTwo)
	{
		m_fAngle += m_fSpeed;

		float fOrgAngle = m_fAngle;

		m_tInfo.fX += m_fDiagonal * cosf(m_fAngle * (PI / 360.f));  //sinf(m_fAngle * (PI / 270.f));
		m_tInfo.fY -= m_fDiagonal * sinf(m_fAngle * (PI / 270.f)); // cosf(m_fAngle * (PI / 360.f));

		m_HInfo.fX += m_fDiagonal * cosf(m_fAngle * (PI / 360.f));
		m_HInfo.fY -= m_fDiagonal * sinf(m_fAngle * (PI / 270.f));

		if (m_dwDustTime + 100 < GetTickCount())
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayer_Dust>::Create((float)m_HRect.right - 50.f, m_tInfo.fY + 150.f));
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayer_Dust>::Create((float)m_HRect.right + 30.f, m_tInfo.fY + 100.f));
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayer_Dust>::Create((float)m_HRect.right - 10.f, m_tInfo.fY + 125.f));
			m_dwDustTime = GetTickCount();
		}
	}

	/*if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_PARRY)->size() == 0)
	{
		m_bPhaseThree = true;
		m_bPhaseOne = false;
		m_bPhaseTwo = false;
	}*/

	/*else if (m_eCurState == ATTACK)
	{*/
	//if (m_dwDashTime + 3000 < GetTickCount())
	//{
	//	CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonster_Dead_Effect>::Create((float)m_HInfo.fX - 50.f, m_HInfo.fY - 40.f));
	//	//CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonster_Dead_Effect>::Create((float)m_HRect.right - 50.f, m_tInfo.fY - 20.f));
	//	m_dwDashTime = GetTickCount();
	//}
//}


	if (m_bPhaseOne || m_bPhaseThree)
	{
		Update_Controller();
	}

	Update_Rect();
	Motion_Change();
	Move_Frame();



	return OBJ_NOEVENT;

}

void CSagittarius::Check_PhaseTwo(void)
{
	if (m_bPhaseTwo && !m_bPhaseOne && !m_bPhaseThree)
	{
		if (m_dwStarCoolTime + 500 < GetTickCount())
		{
			if (m_iStarCnt < m_iStarMaxCnt)
			{
				m_iStarCnt++;

				if (GetTickCount() % 2 == 0)
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CStar>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT));
				if (GetTickCount() % 2 == 1)
					CObjMgr::Get_Instance()->Add_Object(OBJ_PARRY, CAbstractFactory<CStar>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RU));

				//cout << "STAR" << endl;
				m_dwStarCoolTime = GetTickCount();

			}
		}

	}
}


void CSagittarius::Late_Update(void)
{
}

void CSagittarius::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_bPhaseOne || m_bPhaseThree)
	{
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
			RGB(1, 1, 1));	// 제거할 픽셀의 색상

	}
	//	Rectangle(hDC, m_HRect.left + iScrollX, m_HRect.top + iScrollY, m_HRect.right + iScrollX, m_HRect.bottom + iScrollY);
}

void CSagittarius::Release(void)
{
}

void CSagittarius::Collision_Event(CObj * _OtherObj, float fColX, float fColY)
{
	CBullet*	pBullet = dynamic_cast<CBullet*>(_OtherObj);

	if (pBullet)
	{
		if (pBullet->Get_Dead()) return;
		m_fHp -= pBullet->Get_Damage();

	}
	if (m_bFisrtTime)
	{
		if (m_fHp < m_fMaxHp * 0.5f)
		{
			m_HInfo.fCX = 0.f;
			m_HInfo.fCY = 0.f;
			Update_Rect();
			m_bPhaseOne = false;
			m_bPhaseTwo = true;
			m_bPhaseThree = false;
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBigCloud>::Create(m_tInfo.fX, m_tInfo.fY));
			m_bFisrtTime = false;

		}
	}
	if (m_fHp <= EPSILON)
	{
		m_bDead = true;
	}
}

void CSagittarius::Update_Controller()
{
	if (m_bDead) return;

	if (ShootStateTimer.Check())
	{
		m_bShootState = !m_bShootState;
		m_iShootCnt = 0;
	}


	if (m_bShootState && ShootStateCoolTimer.Check())
	{
		m_eCurState = ATTACK;

		if (m_iShootCnt < m_iShootMaxCnt)
		{
			m_iShootFrameCnt = 0;
			m_iShootCnt++;
		}
		if (m_iShootCnt >= m_iShootMaxCnt)
			m_eCurState = IDLE;

	}

	/*if (ShootTimer.Check())
	{
		m_bShoot_Start = !m_bShoot_Start;
		m_iShootCnt = 0;
	}

	if (m_bShoot_Start && ShootCoolTimer.Check())
	{
		if (m_iShootCnt < m_iShootMaxCnt)
		{
			m_iShootFrameCnt = 0;
			m_iShootCnt++;
		}
	}*/

	if (m_iShootFrameCnt <= m_iShootFrameMaxCnt)
	{
		if (m_iShootFrameCnt == m_iShootFrameMaxCnt)
		{
			if (m_bPhaseOne)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, CAbstractFactory<CArrow>::Create(m_HInfo.fX, m_HInfo.fY, DIR_LEFT));
			}
			else if (m_bPhaseThree)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CArrow>::Create(m_HInfo.fX, m_HInfo.fY, DIR_LEFT));
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CStar>::Create(m_HInfo.fX, m_HInfo.fY, DIR_RIGHT));
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CStar>::Create(m_HInfo.fX, m_HInfo.fY, DIR_LU));
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CStar>::Create(m_HInfo.fX, m_HInfo.fY, DIR_LD));
			}
			// 2페이즈 화살 쏠 때 별도 같이 쏘기
			//	/*CObj* pPotato = CAbstractFactory<CPotato_Bullet>::Create(m_HInfo.fX - 150, m_HInfo.fY + 160, DIR_LEFT);
			//	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, pPotato);
			//	CObj* pPotato_Effect = CAbstractFactory<CPotato_Bullet_Effect>::Create(m_HInfo.fX - 180, m_HInfo.fY + 100);
			//	CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, pPotato_Effect);*/
			//}
		}
		m_iShootFrameCnt++;
	}
}



void CSagittarius::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case INTRO_STAR:
			m_pFrameKey = L"Sagittarius_Intro";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case INTRO:
			m_pFrameKey = L"Sagittarius_Intro";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iMotion = 1;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case IDLE:
			m_pFrameKey = L"Sagittarius_Idle";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ATTACK:
			m_pFrameKey = L"Sagittarius_Attack";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 17;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 60;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CSagittarius::Sagittarius_Intro_Star(void)
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

void CSagittarius::Sagittarius_Intro(void)
{
	if (m_bIsIntro_Second)
	{
		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			m_eCurState = IDLE;
			m_bIsIntro_Second = false;
		}
	}
}

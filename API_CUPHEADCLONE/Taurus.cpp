#include "stdafx.h"
#include "Taurus.h"
#include "ObjMgr.h"
#include "Bullet_Effect.h"
#include "EffectMgr.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Sagittarius.h"
#include "Player.h"
#include "Player_Dust.h"
#include "Monster_Dead_Effect.h"
#include "Cloud.h"
#include "Red_Cloud.h"
CTaurus::CTaurus()
	: m_eCurState(INTRO_STAR), m_ePreState(INTRO_STAR)
{
}


CTaurus::~CTaurus()
{
	Release();
}

void CTaurus::Initialize(void)
{
	m_tInfo.fCX = 700.f;
	m_tInfo.fCY = 700.f;

	m_HInfo.fCX = 330.f;
	m_HInfo.fCY = 130.f;


	m_fHp = 3.f;

	//When the Potato Bullet Create
	//ShootTimer.InitLoop(9.1f);
	////The Potato Bullet Distance 
	//ShootCoolTimer.InitLoop(1.3f);

	ShootStateTimer.InitLoop(4.f);
	//ShootStateCoolTimer.InitLoop(1.1f);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Taurus/Taurus_Idle_Pink.bmp", L"Taurus_Idle_Pink");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Taurus/Taurus_Attack_Pink.bmp", L"Taurus_Attack_Pink");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Taurus/Taurus_Idle.bmp", L"Taurus_Idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Taurus/Taurus_Attack.bmp", L"Taurus_Attack");

	m_fDiagonal = 7.f;
	m_fSpeed = 2.5f;

	m_pFrameKey = L"Taurus_Idle";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	m_dwTimer = GetTickCount();

	fDash_Speed = m_fSpeed * 10.f;
	m_bIsIntro_First = true;


	m_eRenderGroup = GAMEOBJECT;
}

int CTaurus::Update(void)
{
	if (m_bDead)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CSagittarius>::Create(6500.f, 1500.f));
		return OBJ_DEAD;
	}
	if (m_eCurState == IDLE)
	{
		m_fAngle += m_fSpeed;

		float fOrgAngle = m_fAngle;

		m_tInfo.fX += m_fDiagonal * sinf(m_fAngle * (PI / 270.f));
		m_tInfo.fY -= m_fDiagonal * cosf(m_fAngle * (PI / 360.f));

		m_HInfo.fX += m_fDiagonal * sinf(m_fAngle * (PI / 270.f));
		m_HInfo.fY -= m_fDiagonal * cosf(m_fAngle * (PI / 360.f));

		if (m_dwDustTime + 100 < GetTickCount())
		{
			//CObj* pTaurus_Dust = CAbstractFactory<CPlayer_Dust>::Create((float)m_HRect.right, m_tInfo.fY - 50.f);
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayer_Dust>::Create((float)m_HRect.right - 50.f, m_tInfo.fY - 50.f));
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CPlayer_Dust>::Create((float)m_HRect.right - 50.f, m_tInfo.fY));
			m_dwDustTime = GetTickCount();
		}
	}
	else if (m_eCurState == ATTACK)
	{
		m_tInfo.fX -= fDash_Speed;
		m_HInfo.fX -= fDash_Speed;

		if (m_dwDashTime + 3000 < GetTickCount())
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonster_Dead_Effect>::Create((float)m_HRect.right - 50.f, m_tInfo.fY - 40.f));
			//CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonster_Dead_Effect>::Create((float)m_HRect.right - 50.f, m_tInfo.fY - 20.f));
			m_dwDashTime = GetTickCount();
		}
	}
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();


	Taurus_Intro();
	Taurus_Intro_Star();


	Dash_Attack();
	Update_Controller();

	Shake_Window();
	Motion_Change();
	Move_Frame();


	Update_Rect();

	return OBJ_NOEVENT;
}

void CTaurus::Late_Update(void)
{
	/*if (m_tInfo.fX >= WINCX)
	{
		this->Set_Pos(0, 0);
	}*/
	//if (m_tInfo.fX <= 6000)
	//{
	//	this->Set_Pos(6300.f, 1100.f);
	//}
}

void CTaurus::Render(HDC hDC)
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
		RGB(1, 1, 1));	// 제거할 픽셀의 색상

		//Rectangle(hDC, m_HRect.left + iScrollX, m_HRect.top + iScrollY, m_HRect.right + iScrollX, m_HRect.bottom + iScrollY);
}

void CTaurus::Release(void)
{
}

void CTaurus::Collision_Event(CObj * _OtherObj, float fColX, float fColY)
{
	CBullet*	pBullet = dynamic_cast<CBullet*>(_OtherObj);
	if (pBullet)
	{
		//m_fHp -= pBullet->Get_Damage();

	}

	if (m_fHp <= EPSILON)
	{
		m_bDead = true;
	}

	CCloud*		pCloud = dynamic_cast<CCloud*>(_OtherObj);
	if (pCloud)
	{
		if (m_eCurState == ATTACK)
		{
			pCloud->Kill_Obj();
			m_bIsColl = true;
		}

	}

	CRed_Cloud*		pRCloud = dynamic_cast<CRed_Cloud*>(_OtherObj);
	if (pRCloud)
	{
		if (m_eCurState == ATTACK && !lstrcmp(m_pFrameKey, L"Taurus_Attack"))
		{
			pRCloud->Kill_Obj();

			m_pFrameKey = L"Taurus_Attack_Pink";

			m_bRed = true;
		}

	}


}

void CTaurus::Update_Controller()
{
	if (m_bDead) return;

	if (ShootStateTimer.Check())
	{
		m_bShootState = true;
	}

	//else
		//m_eCurState = IDLE;

	//if (ShootTimer.Check())
	//{
	//	m_bShoot_Start = !m_bShoot_Start;
	//}

	//if (m_bShoot_Start && ShootCoolTimer.Check())
	//{
	//	//m_tInfo.fX = m_pTarget->Get_Info().fX 

	//	// X값은 변하지 않고 Y값만 이동, Y값이 같아지면 공격
	//	if (m_tInfo.fY == m_pTarget->Get_Info().fY)
	//	{
	//	
	//		Dash_Attack();
	//	}
	//}

}

void CTaurus::Dash_Attack()
{

	if (fabs(m_pTarget->Get_HInfo().fY - m_HInfo.fY) < 30.f)
	{
		if (m_bShootState)
		{
			m_eCurState = ATTACK;
			/*CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonster_Dead_Effect>::Create((float)m_HRect.right - 50.f, m_tInfo.fY - 40.f));
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonster_Dead_Effect>::Create((float)m_HRect.right - 50.f, m_tInfo.fY - 20.f));*/
		}
	}
	if (m_eCurState == ATTACK && m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
	{
		this->Set_Pos(6800.f, 1100.f);
		m_fAngle = fOrgAngle;
	}

	if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
	{
		m_bShootState = false;
		m_eCurState = IDLE;
	}
}

void CTaurus::Shake_Window(void)
{
	if (m_bIsColl && m_bScrollShake && m_iShakeCnt < m_iShakeMaxCnt && m_dwShaketimer + 20 < GetTickCount())
	{
		float fShakeMount = m_iShakeCnt % 2 == 0 ? -10.f : 10.f;
		CScrollMgr::Get_Instance()->Set_ScrollX(fShakeMount);
		m_dwShaketimer = GetTickCount();
		++m_iShakeCnt;
	}
	m_bIsColl = false;
}

void CTaurus::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case INTRO_STAR:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case INTRO:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.iMotion = 1;
			m_tFrame.dwFrameSpeed = 90;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case IDLE:
			if (m_bRed)
				m_pFrameKey = L"Taurus_Idle_Pink";
			else
				m_pFrameKey = L"Taurus_Idle";

			m_tInfo.fCX = 700.f;
			m_tInfo.fCY = 700.f;
			m_HInfo.fCX = 330.f;
			m_HInfo.fCY = 130.f;
			m_iShakeCnt = 0;

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.iMotion = 2;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ATTACK:
			if (m_bRed)
				m_pFrameKey = L"Taurus_Attack_Pink";
			else
				m_pFrameKey = L"Taurus_Attack";
			m_tInfo.fCX = 1200.f;
			m_tInfo.fCY = 500.f;
			m_HInfo.fCX = 1200.f;
			m_HInfo.fCY = 110.f;
			m_iShakeCnt = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 20;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameSpeed = 10;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CTaurus::Taurus_Intro_Star(void)
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

void CTaurus::Taurus_Intro(void)
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

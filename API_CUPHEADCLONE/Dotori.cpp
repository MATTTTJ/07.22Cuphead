#include "stdafx.h"
#include "Dotori.h"
#include "ObjMgr.h"
#include "Bullet_Effect.h"
#include "EffectMgr.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Player.h"

CDotori::CDotori()
	: m_eCurState(WALK), m_ePreState(MOTION_END)
{
}


CDotori::~CDotori()
{
	Release();
}

void CDotori::Initialize(void)
{
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 150.f;

	m_HInfo.fCX = 140.f;
	m_HInfo.fCY = 140.f;

	m_fSpeed = 8.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Enemy/Dotori/Dotori.bmp", L"Dotori");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Enemy/Dotori/Dotori_Attack.bmp", L"Dotori_Attack"); // fCX 526 fCY 512
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Idle.bmp", L"Potato_Idle"); // fCX 526 fCY 512

	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Spit_Attack.bmp", L"Potato_Attack");// fCX 526 fCY 512
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Death.bmp", L"Potato_Death"); // fCX 332 fCY 512

	m_pFrameKey = L"Dotori";
	CSoundMgr::Get_Instance()->PlaySound(L"Acorn_propeller_1.wav", SOUND_EFFECT, 1.f);
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 10;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_dwTimer = GetTickCount();
	m_eDir = DIR_LEFT;
	m_fStartX = m_tInfo.fX;
	m_bIsIntro_First = false;
	m_eRenderGroup = GAMEOBJECT;
	m_bFirstRender = false;
}

int CDotori::Update(void)
{
	if (m_bDead)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		return OBJ_DEAD;
	}
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	if (m_eDir == DIR_LEFT)
	{
			m_tFrame.iMotion = 0;
			m_tInfo.fX -= m_fSpeed;
			m_HInfo.fX -= m_fSpeed;
	}
	else if (m_eDir == DIR_RIGHT)
	{
		m_tFrame.iMotion = 1;
		m_tInfo.fX += m_fSpeed;
		m_HInfo.fX += m_fSpeed;
	}

	Drop_Dotori();

	if ( m_eDir == DIR_DOWN)
	{
		m_tInfo.fY += m_fSpeed;
		m_HInfo.fY += m_fSpeed;
		Move_Frame(10);
	}

	Motion_Change();
	Move_Frame();
	Update_Rect();


		return OBJ_NOEVENT;
	}

	void CDotori::Late_Update(void)
	{
		if (m_tInfo.fCY < 0)
			m_bDead = true;
	}

	void CDotori::Render(HDC hDC)
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

		int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
		if (m_bFirstRender)
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
		m_bFirstRender = true;
		//Rectangle(hDC, m_HRect.left + iScrollX, m_HRect.top + iScrollY, m_HRect.right + iScrollX, m_HRect.bottom + iScrollY);
	}

	void CDotori::Release(void)
	{
	}

	void CDotori::Collision_Event(CObj * _OtherObj, float fColX, float fColY)
	{
		CBullet*	pBullet = dynamic_cast<CBullet*>(_OtherObj);
		if (pBullet)
		{
			m_fHp -= pBullet->Get_Damage();
		}

		if (m_fHp <= EPSILON)
		{
			m_bDead = true;
		}
	}

	void CDotori::Drop_Dotori(void)
	{
		if (fabs(m_pTarget->Get_Info().fX - m_tInfo.fX) < 100.f)
		{
			if (!m_bIsIntro_First)
			{
				m_eCurState = ATTACK;
				m_eDir = DIR_DOWN;
				m_bIsIntro_First = true;

				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"Acorn_drop.wav", SOUND_EFFECT, 1.f);


			}
		}
	}

	void CDotori::Motion_Change(void)
	{
		if (m_ePreState != m_eCurState)
		{
			switch (m_eCurState)
			{
			case WALK:
				if (m_eDir == DIR_LEFT)
				{
					m_pFrameKey = L"Dotori";
					m_tFrame.iFrameStart = 0;
					m_tFrame.iFrameEnd = 10;
					m_tFrame.iMotion = 0;
					m_tFrame.dwFrameSpeed = 100;
					m_tFrame.dwFrameTime = GetTickCount();
				}
				else
				{
					m_pFrameKey = L"Dotori";
					m_tFrame.iFrameStart = 0;
					m_tFrame.iFrameEnd = 10;
					m_tFrame.iMotion = 1;
					m_tFrame.dwFrameSpeed = 100;
					m_tFrame.dwFrameTime = GetTickCount();
				}
				break;

			case ATTACK:
				m_pFrameKey = L"Dotori_Attack";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 10;
				m_tFrame.iMotion = 0;
				m_tFrame.dwFrameSpeed = 30;
				m_tFrame.dwFrameTime = GetTickCount();
				break;
			}
			m_eCurState = m_ePreState;
		}
	}

#include "stdafx.h"
#include "Bullet.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Player.h"
#include "Potato.h"
#include "ObjMgr.h"
#include "Bullet_Effect.h"
#include "AbstractFactory.h"
#include "LineMgr.h"
#include "Bullet_Death.h"
#include "SoundMgr.h"
CBullet::CBullet()
{
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize(void)
{
	m_tInfo.fCX = 77.f;
	m_tInfo.fCY = 75.f;
	
	m_HInfo.fCX = 77.f;
	m_HInfo.fCY = 18.f;
	m_HInfo.m_fDamage = 1.f;
	m_fSpeed = 10.f;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Bullet/Circle/Circle_0.bmp", L"Bullet_Default");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Bullet/Circle/Bullet_Default_Death.bmp", L"Bullet_Default_Death");
	m_pFrameKey = L"Bullet_Default";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 80;
	m_tFrame.dwFrameTime = GetTickCount();
	m_iJumpCnt = 0;
	m_fCurJumpSpeed = m_fInitJumpSpeed;
	m_bJump = false;
	


	m_eRenderGroup = GAMEOBJECT;
}

int CBullet::Update(void)
{
	if (m_bDead)
	{

		return OBJ_DEAD;
	}



	switch (m_eDir)
		{
		case DIR_LEFT:
			m_tInfo.fX -= m_fSpeed;
			m_HInfo.fX -= m_fSpeed;

			m_tInfo.fY -= m_fCurJumpSpeed;
			m_HInfo.fY -= m_fCurJumpSpeed;
			if (fabs(m_fCurJumpSpeed) < m_fMaxAbsJumpSpeed) // limit max speed
				m_fCurJumpSpeed -= GRAVITY;

			break;

		case DIR_RIGHT:
			m_tInfo.fX += m_fSpeed;
			m_HInfo.fX += m_fSpeed;

			m_tInfo.fY -= m_fCurJumpSpeed;
			m_HInfo.fY -= m_fCurJumpSpeed;
			if (fabs(m_fCurJumpSpeed) < m_fMaxAbsJumpSpeed) // limit max speed
				m_fCurJumpSpeed -= GRAVITY;

			break;

		case DIR_UP:
			m_tInfo.fY -= m_fSpeed;
			m_HInfo.fY -= m_fSpeed;
			break;

		case DIR_DOWN:
			m_tInfo.fY += m_fSpeed;
			m_HInfo.fY += m_fSpeed;
			break;

		case DIR_LU:
			m_tInfo.fX -= m_fSpeed * 1.25f;
			m_HInfo.fX -= m_fSpeed * 1.25f;

			m_tInfo.fY -= m_fCurJumpSpeed;
			m_HInfo.fY -= m_fCurJumpSpeed;
			if (fabs(m_fCurJumpSpeed) < m_fMaxAbsJumpSpeed) // limit max speed
				m_fCurJumpSpeed -= GRAVITY;
			break;
	
		case DIR_RU:
			m_tInfo.fX += m_fSpeed * 1.25f;
			m_HInfo.fX += m_fSpeed * 1.25f;

			m_tInfo.fY -= m_fCurJumpSpeed;
			m_HInfo.fY -= m_fCurJumpSpeed;
			if (fabs(m_fCurJumpSpeed) < m_fMaxAbsJumpSpeed) // limit max speed
				m_fCurJumpSpeed -= GRAVITY;
			break;

		}	
	float fY = 0.f;

	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX,m_tInfo.fY, &fY);
	
	if (bLineCol && abs(fY - m_tInfo.fY) < m_fMaxAbsJumpSpeed * 0.9f && m_iJumpCnt < m_iJumpMaxCnt)
	{
		m_bJump = false;
		m_fInitJumpSpeed *= 0.8f;
		m_fCurJumpSpeed = m_fInitJumpSpeed;
		m_iJumpCnt++;
		CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER);
		if (GetTickCount() % 3 == 0)
			CSoundMgr::Get_Instance()->PlaySound(L"Bounceball_bounce1.wav", SOUND_PLAYER, 1.f);
		else if (GetTickCount() % 3 == 1)
			CSoundMgr::Get_Instance()->PlaySound(L"Bounceball_bounce2.wav", SOUND_PLAYER, 1.f);
		else if (GetTickCount() % 3 == 2)
			CSoundMgr::Get_Instance()->PlaySound(L"Bounceball_bounce3.wav", SOUND_PLAYER, 1.f);
	/*	else if (GetTickCount() % 5 == 3)
			CSoundMgr::Get_Instance()->PlaySound(L"sfx_player_weapon_bouncer_004.wav", SOUND_PLAYER, 1.f);
		else if (GetTickCount() % 5 == 4)
			CSoundMgr::Get_Instance()->PlaySound(L"sfx_player_weapon_bouncer_005.wav", SOUND_PLAYER, 1.f);*/
		if (m_iJumpCnt >= m_iJumpMaxCnt)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBullet_Death>::Create(m_tInfo.fX, m_tInfo.fY));
			m_bDead = true;
		}
	}
	

	Move_Frame(4);
	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update(void)
{
	//if ( 100 >= m_tRect.left || 
	//	WINCX - 100 <= m_tRect.right || 
	//	100 >= m_tRect.top ||
	//	WINCY - 100 <= m_tRect.bottom )
	//{
	//	m_bDead = true;
	//}
}

void CBullet::Render(HDC hDC)
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
	/*HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Ellipse(hDC, m_tRect.left + iScrollX, m_tRect.top+ iScrollY, m_tRect.right + iScrollX, m_tRect.bottom+ iScrollY);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);*/
}

void CBullet::Release(void)
{
	
}

void CBullet::Collision_Event(CObj * _OtherObj, float _fColX, float _fColY)
{
	CMonster* pMonster = dynamic_cast<CMonster*>(_OtherObj);
	if (pMonster)
	{
		m_bDead = true;
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBullet_Death>::Create(m_tInfo.fX, m_tInfo.fY));

		/*if (_fColX < _fColY && m_tInfo.fX > _OtherObj->Get_Info().fX)
			dynamic_cast<CHit_Effect*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_EFFECT)->back())->Set_Dir(LOOK_LEFT);

		else if (_fColX < _fColY && m_tInfo.fX < _OtherObj->Get_Info().fX)
			dynamic_cast<CHit_Effect*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_EFFECT)->back())->Set_Dir(LOOK_RIGHT);*/
	}

	/*CPlayer* pPlayer = dynamic_cast<CPlayer*>(_OtherObj);
	if (pPlayer)
	{
		m_bDead = true;
	}*/

}

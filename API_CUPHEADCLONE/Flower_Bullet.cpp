#include "stdafx.h"
#include "Flower_Bullet.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Player.h"
#include "Potato.h"
#include "ObjMgr.h"
#include "Bullet_Effect.h"
#include "AbstractFactory.h"
#include "LineMgr.h"
#include "Bullet_Death.h"
#include "Flower_Bullet_Dead.h"

CFlower_Bullet::CFlower_Bullet()
{
}


CFlower_Bullet::~CFlower_Bullet()
{
	Release();
}

void CFlower_Bullet::Initialize(void)
{
	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 200.f;

	m_HInfo.fCX = 35.f;
	m_HInfo.fCY = 50.f;

	m_HInfo.m_fDamage = 1.f;
	m_fSpeed = 10.f;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Enemy/Flower/Flower.bmp", L"Flower");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Bullet/Circle/Bullet_Default_Death.bmp", L"Bullet_Default_Death");
	m_pFrameKey = L"Flower";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iMotion = 2;
	m_tFrame.dwFrameSpeed = 60;
	m_tFrame.dwFrameTime = GetTickCount();

	m_iJumpCnt = 0;
	m_fCurJumpSpeed = m_fInitJumpSpeed;
	m_bJump = false;
	m_bFirstRender = false;


	m_eRenderGroup = GAMEOBJECT;
}

int CFlower_Bullet::Update(void)
{
	if (m_bDead)
	{
		//CScrollMgr::Get_Instance()->Shake();
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
	}

	float fY = 0.f;

	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);

	if (bLineCol && abs(fY - m_tInfo.fY) < m_fMaxAbsJumpSpeed * 1.5f && m_iJumpCnt < m_iJumpMaxCnt)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CFlower_Bullet_Dead>::Create(m_tInfo.fX, m_tInfo.fY));
		m_bIsExploded = true;
		m_bDead = true;
	}
	Update_Shake();

	Move_Frame(4);
	Update_Rect();

	return OBJ_NOEVENT;
}

void CFlower_Bullet::Late_Update(void)
{
}

void CFlower_Bullet::Render(HDC hDC)
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
}

void CFlower_Bullet::Release(void)
{
}

void CFlower_Bullet::Collision_Event(CObj * _OtherObj, float _fColX, float _fColY)
{
	CMonster* pMonster = dynamic_cast<CMonster*>(_OtherObj);
	if (pMonster)
	{
		m_bIsExploded = true;
		m_bDead = true;
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CFlower_Bullet_Dead>::Create(m_tInfo.fX, m_tInfo.fY));

		/*if (_fColX < _fColY && m_tInfo.fX > _OtherObj->Get_Info().fX)
		dynamic_cast<CHit_Effect*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_EFFECT)->back())->Set_Dir(LOOK_LEFT);

		else if (_fColX < _fColY && m_tInfo.fX < _OtherObj->Get_Info().fX)
		dynamic_cast<CHit_Effect*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_EFFECT)->back())->Set_Dir(LOOK_RIGHT);*/
	}
}

void CFlower_Bullet::Update_Shake(void)
{
	if (m_bIsExploded && m_bScrollShake && m_iShakeCnt < m_iShakeMaxCnt && m_dwShaketimer + 20 < GetTickCount())
	{
		float fShakeMount = m_iShakeCnt % 2 == 0 ? -10.f : 10.f;
		CScrollMgr::Get_Instance()->Set_ScrollX(fShakeMount);
		m_dwShaketimer = GetTickCount();
		++m_iShakeCnt;

		if (m_iShakeCnt >= m_iShakeMaxCnt)
			m_bIsExploded = false;
	}
}

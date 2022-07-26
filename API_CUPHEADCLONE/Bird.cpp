#include "stdafx.h"
#include "Bird.h"
#include "ObjMgr.h"
#include "Bullet_Effect.h"
#include "EffectMgr.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Monster_Dead_Effect.h"

CBird::CBird()
{
}


CBird::~CBird()
{
	Release();
}

void CBird::Initialize(void)
{
	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 200.f;

	m_HInfo.fCX = 150.f;
	m_HInfo.fCY = 150.f;

	m_fSpeed = 8.f;
	m_fDiagonal = 5.f;

	m_fHp = 2.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Enemy/Bird/Bird.bmp", L"Bird");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Intro.bmp", L"Potato_Intro"); // fCX 526 fCY 512
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Idle.bmp", L"Potato_Idle"); // fCX 526 fCY 512

	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Spit_Attack.bmp", L"Potato_Attack");// fCX 526 fCY 512
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Potato/Potato_Death.bmp", L"Potato_Death"); // fCX 332 fCY 512

	m_pFrameKey = L"Bird";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 15;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_dwTimer = GetTickCount();

	m_eRenderGroup = GAMEOBJECT;
}

int CBird::Update(void)
{
	if (m_bDead)
	{
		if (m_tFrame.iFrameStart == 0)
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonster_Dead_Effect>::Create(m_tInfo.fX + (rand() % 300), m_tInfo.fY + (rand() % 300)));
			//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<COnion>::Create());
			return OBJ_DEAD;
	}

	//
	//

	m_fAngle += m_fSpeed;

	m_tInfo.fX -= m_fSpeed;
	m_tInfo.fY -= m_fDiagonal* cosf(m_fAngle * (PI / 180.f));

	m_HInfo.fX -= m_fSpeed;
	m_HInfo.fY -= m_fDiagonal* cosf(m_fAngle * (PI / 180.f));

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CBird::Late_Update(void)
{
	if (m_HRect.right < 0.f)
		m_bDead = true;
}

void CBird::Render(HDC hDC)
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
}

void CBird::Release(void)
{
}

void CBird::Collision_Event(CObj * _OtherObj, float fColX, float fColY)
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
	/*CCharging_Bullet*	pChargind_Bullet = dynamic_cast<CCharging_Bullet*>(_OtherObj);
	if (pChargind_Bullet)
	{
	m_fHp -= pChargind_Bullet->Get_Damage();
	}*/
}



#include "stdafx.h"
#include "Carrot_Bullet.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Player.h"
#include "Potato.h"
#include "ObjMgr.h"
#include "Bullet_Effect.h"
#include "AbstractFactory.h"
#include "Carrot_Splash_Effect.h"

CCarrot_Bullet::CCarrot_Bullet()
{
}


CCarrot_Bullet::~CCarrot_Bullet()
{
	Release();
}

void CCarrot_Bullet::Initialize(void)
{
	m_tInfo.fCX = 82.f;
	m_tInfo.fCY = 137.f;

	m_HInfo.fCX = 82.f;
	m_HInfo.fCY = 110.f;

	m_HInfo.m_fDamage = 1.f;
	m_fSpeed = 6.f;
	
	// X�� �̵������� Y�� �̵����� �� Ŀ�� ���ϱ� ��������. 

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Carrot/Carrot_Missile.bmp", L"Carrot_Missile");

	m_pFrameKey = L"Carrot_Missile";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 40;
	m_tFrame.dwFrameTime = GetTickCount();
	m_eRenderGroup = GAMEOBJECT;
}

int CCarrot_Bullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	
	if (m_pTarget)
	{
		float	fWidth = m_pTarget->Get_HInfo().fX - m_HInfo.fX;
		float	fHeight = m_pTarget->Get_HInfo().fY - m_HInfo.fY;

		m_fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		float	fRadian = acosf(fWidth / m_fDiagonal);

		m_fAngle = fRadian * 180.f / PI;

		if (m_pTarget->Get_HInfo().fY > m_HInfo.fY)
			m_fAngle *= -1.f;

		m_tInfo.fX += cosf(m_fAngle * (PI / 180.f)) * (m_fSpeed * 0.7f);
		m_HInfo.fX += cosf(m_fAngle * (PI / 180.f)) * (m_fSpeed * 0.7f);
	}
	
	m_tInfo.fY += 5.f; 
	m_HInfo.fY += 5.f; 


	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CCarrot_Bullet::Late_Update(void)
{
	if (900 <= m_HRect.bottom)
	{
		m_bDead = true;
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CCarrot_Splash_Effect>::Create(m_tInfo.fX, m_tInfo.fY));
	}
}

void CCarrot_Bullet::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,	// ���� ���� ��ġ�� ��ǥ ����(x,y ����)
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,		// ���� ���� �̹����� ���� ����(����, ���μ���)
		(int)m_tInfo.fCY,
		hMemDC,					// ��Ʈ���� ������ �ִ� dc
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,						// ����� ��Ʈ�� ���� ��ǥ(x,y ����)
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,			// ���� �� ��Ʈ�� �� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));	// ������ �ȼ��� ����
}

void CCarrot_Bullet::Release(void)
{
}

void CCarrot_Bullet::Collision_Event(CObj * _OtherObj, float _fColX, float _fColY)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_OtherObj);
	if (pPlayer)
	{
		m_bDead = true;

		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CCarrot_Splash_Effect>::Create(m_tInfo.fX, m_tInfo.fY));
	}
}

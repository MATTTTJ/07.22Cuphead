#include "stdafx.h"
#include "Carrot_Beam.h"
#include "Carrot_Bullet.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Player.h"
#include "Potato.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

CCarrot_Beam::CCarrot_Beam()
{
}


CCarrot_Beam::~CCarrot_Beam()
{
	Release();
}

void CCarrot_Beam::Initialize(void)
{
	m_tInfo.fCX = 171.f;
	m_tInfo.fCY = 163.f;

	m_HInfo.fCX = 171.f;
	m_HInfo.fCY = 163.f;

	m_HInfo.m_fDamage = 1.f;
	m_fSpeed = 8.f;

	// X�� �̵������� Y�� �̵����� �� Ŀ�� ���ϱ� ��������. 

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Carrot/Carrot_BeamProj.bmp", L"Carrot_BeamProj");

	m_pFrameKey = L"Carrot_BeamProj";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 8;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_eRenderGroup = GAMEOBJECT;

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);
	if (m_pTarget)
	{
		float	fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
		float	fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

		m_fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
	
		m_fDX = fWidth / m_fDiagonal;
		m_fDY = fHeight / m_fDiagonal;
	}


}

int CCarrot_Beam::Update(void)
{
	Move_Frame(10);

	if (m_bDead || m_tFrame.iFrameStart >= 10)
		return OBJ_DEAD;


	m_tInfo.fX += m_fSpeed * m_fDX;
	m_HInfo.fX += m_fSpeed * m_fDX;
	m_tInfo.fY += m_fSpeed * m_fDY;
	m_HInfo.fY += m_fSpeed * m_fDY;


	Update_Rect();
	return OBJ_NOEVENT;
}

void CCarrot_Beam::Late_Update(void)
{
	if (800 <= m_HRect.bottom)
	{
		m_bDead = true;
	}
}

void CCarrot_Beam::Render(HDC hDC)
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

void CCarrot_Beam::Release(void)
{
}

void CCarrot_Beam::Collision_Event(CObj * _OtherObj, float _fColX, float _fColY)
{
}

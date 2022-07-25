#include "stdafx.h"
#include "Star.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Cloud.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Cloud_Dead.h"
#include "DeadEventMgr.h"
#include "Bullet.h"
CStar::CStar()
{
}


CStar::~CStar()
{
	Release();
}

void CStar::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Sagittarius/Star_BP.bmp", L"Star_BP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Sagittarius/Star_Dead.bmp", L"Star_Dead");

	m_MTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_MONSTER, this);
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	m_pFrameKey = L"Star_BP";

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_HInfo.fCX = 40.f;
	m_HInfo.fCY = 40.f;

	m_fHp = 1.f;

	m_fRotAngle = 0.f;
	m_fRotSpeed = 30.f;
	fCenterX = m_tInfo.fX;
	fCenterY = m_tInfo.fY;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 12;
	m_tFrame.dwFrameSpeed = 70;
	m_tFrame.dwFrameTime = GetTickCount();

	//if (GetTickCount() % 2 == 0)
	//	m_tFrame.iMotion = 0;
	//else
	//	m_tFrame.iMotion = 1;

	m_fDiagonal = 500.f;
	m_fSpeed = 1.f;
	m_dwChaserTime = GetTickCount();
	m_dwLiveTime = GetTickCount();
	Update_Rect();

	m_eRenderGroup = GAMEOBJECT;
}

int CStar::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	switch (m_eDir)
	{
	case DIR_LEFT:
		m_tFrame.iMotion = 1;
		m_fAngle += m_fSpeed;
		m_HInfo.fCX = 20.f;
		m_HInfo.fCY = 20.f;
		m_tInfo.fX = m_MTarget->Get_Info().fX + m_fDiagonal * cosf(m_fAngle * (PI / 180.f));
		m_tInfo.fY = m_MTarget->Get_Info().fY - m_fDiagonal * sinf(m_fAngle * (PI / 180.f));
		m_HInfo.fX = m_MTarget->Get_Info().fX + m_fDiagonal * cosf(m_fAngle * (PI / 180.f));
		m_HInfo.fY = m_MTarget->Get_Info().fY - m_fDiagonal * sinf(m_fAngle * (PI / 180.f));
		break;

	case DIR_RU:
		m_fAngle += m_fSpeed;
		m_tFrame.iMotion = 1;
		//	m_HInfo.fCX = 0.f;
			//m_HInfo.fCY = 0.f;
		m_tInfo.fX = m_MTarget->Get_Info().fX + m_fDiagonal * cosf(m_fAngle * (PI / 180.f));
		m_tInfo.fY = m_MTarget->Get_Info().fY - m_fDiagonal * sinf(m_fAngle * (PI / 180.f));
		m_HInfo.fX = m_MTarget->Get_Info().fX + m_fDiagonal * cosf(m_fAngle * (PI / 180.f));
		m_HInfo.fY = m_MTarget->Get_Info().fY - m_fDiagonal * sinf(m_fAngle * (PI / 180.f));
		break;

	case DIR_RIGHT:

		//if (m_dwChaserTime + 50 < GetTickCount())
		//{
		m_fSpeed = 5.f;
		m_fDiagonal = 300.f;
		//m_fAngle += m_fSpeed;
		m_tFrame.iMotion = 1;

		if (m_pTarget)
		{
			float	fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
			float	fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

			m_fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

			float	fRadian = acosf(fWidth / m_fDiagonal);

			m_fAngle = fRadian * 180.f / PI;

			if (m_pTarget->Get_Info().fY > m_tInfo.fY)
				m_fAngle *= -1.f;
		}
		m_tInfo.fX += cosf(m_fAngle * (PI / 180.f)) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle * (PI / 180.f)) * m_fSpeed;

		/*m_tInfo.fX = m_pTarget->Get_Info().fX + m_fDiagonal * cosf(m_fAngle * (PI / 180.f));
		m_tInfo.fY = m_pTarget->Get_Info().fY - m_fDiagonal * sinf(m_fAngle * (PI / 180.f));
		m_HInfo.fX = m_pTarget->Get_Info().fX + m_fDiagonal * cosf(m_fAngle * (PI / 180.f));
		m_HInfo.fY = m_pTarget->Get_Info().fY - m_fDiagonal * sinf(m_fAngle * (PI / 180.f));*/
		//}
		//m_dwChaserTime = GetTickCount();
		break;

	case DIR_LD:

		//if (m_dwChaserTime + 50 < GetTickCount())
	//	{	
		m_fSpeed = 5.f;

		//m_fAngle += m_fSpeed;
		m_fDiagonal = 300.f;
		m_tFrame.iMotion = 1;

		if (m_pTarget)
		{
			float	fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
			float	fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

			m_fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

			float	fRadian = acosf(fWidth / m_fDiagonal);

			m_fAngle = fRadian * 180.f / PI;

			if (m_pTarget->Get_Info().fY > m_tInfo.fY)
				m_fAngle *= -1.f;
		}
		m_tInfo.fX += cosf(m_fAngle * (PI / 180.f)) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle * (PI / 180.f)) * m_fSpeed;
		/*m_tInfo.fX = m_pTarget->Get_Info().fX + m_fDiagonal * cosf(m_fAngle * (PI / 180.f));
		m_tInfo.fY = m_pTarget->Get_Info().fY + m_fDiagonal * sinf(m_fAngle * (PI / 180.f));
		m_HInfo.fX = m_pTarget->Get_Info().fX + m_fDiagonal * cosf(m_fAngle * (PI / 180.f));
		m_HInfo.fY = m_pTarget->Get_Info().fY + m_fDiagonal * sinf(m_fAngle * (PI / 180.f));*/
		//}
		//m_dwChaserTime = GetTickCount();
		break;

	case DIR_LU:

		//if (m_dwChaserTime + 50 < GetTickCount())
		//{
		m_fSpeed = 5.f;
		m_fDiagonal = 100.f;
		m_tFrame.iMotion = 1;


		/*if (m_pTarget)
		{
			float	fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
			float	fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

			m_fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

			float	fRadian = acosf(fWidth / m_fDiagonal);

		

			if (m_pTarget->Get_Info().fY > m_tInfo.fY)
				m_fAngle *= -1.f;

		}*/
		{
			float	fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
			float	fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

			float fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

			float fToTargetX = fWidth / fDistance;
			float fToTargetY = fHeight / fDistance;

			fCenterX += m_fSpeed * fToTargetX;
			fCenterY += m_fSpeed * fToTargetY;
		}
	


		m_fRotAngle += m_fRotSpeed;

		m_tInfo.fX = fCenterX + m_fDiagonal * cosf(m_fRotAngle * (PI / 180.f));
		m_tInfo.fY = fCenterY - m_fDiagonal * sinf(m_fRotAngle * (PI / 180.f));

		/*m_tInfo.fX + cosf(m_fAngle * (PI / 180.f)) * m_fSpeed;
		m_tInfo.fY + sinf(m_fAngle * (PI / 180.f)) * m_fSpeed;*/
		/*m_tInfo.fX = m_pTarget->Get_Info().fX + m_fDiagonal * cosf(m_fAngle * (PI / 180.f));
		m_tInfo.fY = m_pTarget->Get_Info().fY - m_fDiagonal * sinf(m_fAngle * (PI / 180.f));
		m_HInfo.fX = m_pTarget->Get_Info().fX + m_fDiagonal * cosf(m_fAngle * (PI / 180.f));
		m_HInfo.fY = m_pTarget->Get_Info().fY - m_fDiagonal * sinf(m_fAngle * (PI / 180.f));*/
		//}
		//m_dwChaserTime = GetTickCount();
		break;
	default:
		break;
	}


	//m_tInfo.fX -= m_fSpeed;
	//m_HInfo.fX -= m_fSpeed;

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CStar::Late_Update(void)
{
	if (m_dwLiveTime + 7000 < GetTickCount() && (m_eDir == DIR_RIGHT || m_eDir == DIR_LU || m_eDir == DIR_LD))
	{
		m_bDead = true;
	}
}

void CStar::Render(HDC hDC)
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
		RGB(255, 255, 255));	// 제거할 픽셀의 색상
	Rectangle(hDC, m_HRect.left + iScrollX, m_HRect.top + iScrollY, m_HRect.right + iScrollX, m_HRect.bottom + iScrollY);

}

void CStar::Release(void)
{
}

void CStar::Collision_Event(CObj * _OtherObj, float fColX, float fColY)
{
	CBullet*	pBullet = dynamic_cast<CBullet*>(_OtherObj);

	if (pBullet)
	{
		if (pBullet->Get_Dead()) return;
		m_fHp -= pBullet->Get_Damage();

		if (m_fHp <= EPSILON)
		{
			m_bDead = true;
		}
	}
}

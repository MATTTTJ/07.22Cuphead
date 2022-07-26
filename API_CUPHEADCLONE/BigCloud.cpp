#include "stdafx.h"
#include "BigCloud.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Cloud.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"
CBigCloud::CBigCloud()
{
}


CBigCloud::~CBigCloud()
{
}

void CBigCloud::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Sagittarius/Disapeared.bmp", L"Disapeared");
	m_pFrameKey = L"Disapeared";

	m_tInfo.fCX = 700.f;
	m_tInfo.fCY = 700.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 18;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 40;
	m_tFrame.dwFrameTime = GetTickCount();
	//CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
	
	m_eRenderGroup = GAMEOBJECT;
}

int CBigCloud::Update(void)
{
	Move_Frame();
	Update_Rect();

	if (m_tFrame.iFrameStart >= 18)
		return OBJ_DEAD;



	return OBJ_NOEVENT;
}

void CBigCloud::Late_Update(void)
{
}

void CBigCloud::Render(HDC hDC)
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
		RGB(1, 1, 1));	// ������ �ȼ��� ����
}

void CBigCloud::Release(void)
{
}

#include "stdafx.h"
#include "Root_Stage.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Monster.h"
#include "SoundMgr.h"
#include "Potato.h"
#include "CollisionMgr.h"
#include "Player_UI.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "Press_Z.h"
CRoot_Stage::CRoot_Stage()
{
}


CRoot_Stage::~CRoot_Stage()
{
	Release();
}

void CRoot_Stage::Initialize(void)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(150.f, 700.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CPotato>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CPlayer_UI>::Create(70.f, 770.f));
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Map/Root/Root_BG_1.bmp", L"Root_BG");
	CLineMgr::Get_Instance()->Load_Line(L"../Data/Line_Root.dat");
	CSoundMgr::Get_Instance()->PlayBGM(L"Stage_Root.wav", 0.8f);
}

int CRoot_Stage::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	
	/*if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER)->size() == 0)
	{
		if (CKeyMgr::Get_Instance()->Key_Down('Z'))
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_STAGEFIRST);
		}
	}*/

	if (CObjMgr::Get_Instance()->Get_Player()->Get_HInfo().fX >= 200.f &&
		CObjMgr::Get_Instance()->Get_Player()->Get_HInfo().fX <= 400.f && CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER)->size() == 0)

	{
		if (!m_bIsFirst)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CPress_Z>::
				Create());
			m_bIsFirst = true;
		}
		if (CKeyMgr::Get_Instance()->Key_Down('Z'))
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_STAGEFIRST);
		}
	}
	else
		m_bIsFirst = false;
	return 0;
}

void CRoot_Stage::Late_Update(void)
{


	CObjMgr::Get_Instance()->Late_Update();
	CLineMgr::Get_Instance()->Late_Update();
}

void CRoot_Stage::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Root_BG");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC, iScrollX, iScrollY, 1600, 1000, hMemDC, 0, 0, SRCCOPY);
	CObjMgr::Get_Instance()->Render(hDC);
	//CLineMgr::Get_Instance()->Render(hDC);
}

void CRoot_Stage::Release(void)
{
	CObjMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Destroy_Instance();
	CSoundMgr::Get_Instance()->Destroy_Instance();
}

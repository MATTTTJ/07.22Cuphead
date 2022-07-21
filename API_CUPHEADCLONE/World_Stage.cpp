#include "stdafx.h"
#include "World_Stage.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Monster.h"
#include "SceneMgr.h"
#include "Player_World.h"
#include "Wall.h"
#include "SceneMgr.h"
#include "KeyMgr.h"



CWorld_Stage::CWorld_Stage()
{
}


CWorld_Stage::~CWorld_Stage()
{
	Release();
}

void CWorld_Stage::Initialize(void)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_WORLD, CAbstractFactory<CPlayer_World>::Create(300.f, 300.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(250.f, 280.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(250.f, 330.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(250.f, 380.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(250.f, 430.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(300.f, 430.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(300.f, 480.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(300.f, 530.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(340.f, 530.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(340.f, 560.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(390.f, 570.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(440.f, 570.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(490.f, 570.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(540.f, 570.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(590.f, 530.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(630.f, 510.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(680.f, 510.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(730.f, 510.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(750.f, 540.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(770.f, 560.f));


	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(930.f, 560.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(900.f, 610.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(870.f, 620.f));





	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(250.f, 280.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(300.f, 280.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(350.f, 280.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(400.f, 280.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(400.f, 330.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(400.f, 380.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(430.f, 380.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(430.f, 430.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(430.f, 480.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(480.f, 480.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(480.f, 430.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(530.f, 410.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(580.f, 410.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(630.f, 410.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(680.f, 410.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(730.f, 410.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(780.f, 410.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(780.f, 360.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(780.f, 310.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, Create_Wall(780.f, 260.f));


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Map/World/World_Map.bmp", L"World_Map");
}

int CWorld_Stage::Update(void)
{
	CObjMgr::Get_Instance()->Update();

	

	return 0;
}

void CWorld_Stage::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();

	if (CObjMgr::Get_Instance()->Get_PlayerWorld()->Get_Info().fX >= 1500.f &&
		CObjMgr::Get_Instance()->Get_PlayerWorld()->Get_Info().fY >= 300.f)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGETUTORIAL);
	}

	if (CObjMgr::Get_Instance()->Get_PlayerWorld()->Get_Info().fX >= 800.f &&
		CObjMgr::Get_Instance()->Get_PlayerWorld()->Get_Info().fY >= 200.f)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGEROOT);
	}
}

void CWorld_Stage::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"World_Map");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	BitBlt(hDC, iScrollX, iScrollY, 1666, 934, hMemDC, 0, 0, SRCCOPY);


	//CLineMgr::Get_Instance()->Render(hDC);
	//CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CWorld_Stage::Release(void)
{
	CObjMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Release();
}

CObj * CWorld_Stage::Create_Wall(float _fX, float _fY)
{
	CObj*		pObj = new CWall;
	pObj->Initialize();
	pObj->Set_Pos(_fX, _fY);

	return pObj;
}

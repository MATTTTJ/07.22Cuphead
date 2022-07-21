#include "stdafx.h"
#include "Second_Stage.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "KeyMgr.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "CollisionMgr.h"

#include "Root_Stage.h"
#include "Player.h"
#include "Player_UI.h"

CSecond_Stage::CSecond_Stage()
{
}


CSecond_Stage::~CSecond_Stage()
{
	Release();
}

void CSecond_Stage::Initialize(void)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(200.f, 1700.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CPlayer_UI>::Create(70.f, 770.f));

	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CPotato>::Create());
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Map/Cloud/Cloud_Map_0.bmp", L"Cloud_Map");
	CLineMgr::Get_Instance()->Load_Line(L"../Data/Line_Second.dat");
}

int CSecond_Stage::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CLineMgr::Get_Instance()->Update();

	return 0;
}

void CSecond_Stage::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
	CLineMgr::Get_Instance()->Late_Update();
}

void CSecond_Stage::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Cloud_Map");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC, iScrollX, iScrollY, 7500, 2000, hMemDC, 0, 0, SRCCOPY);
	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);
}

void CSecond_Stage::Release(void)
{
	CObjMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Destroy_Instance();
}

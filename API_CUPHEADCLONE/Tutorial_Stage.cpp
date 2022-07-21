#include "stdafx.h"
#include "Tutorial_Stage.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Monster.h"
#include "SoundMgr.h"

CTutorial_Stage::CTutorial_Stage()
{
}

CTutorial_Stage::~CTutorial_Stage()
{
	Release();
}

void CTutorial_Stage::Initialize(void)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Map/Tutorial/Tutorial_0.bmp", L"Tutorial_Room");
	CLineMgr::Get_Instance()->Initialize();
}

int CTutorial_Stage::Update(void)
{
	/*CTileMgr::Get_Instance()->Update();*/
	CObjMgr::Get_Instance()->Update();
//	CLineMgr::Get_Instance()->Update();


	return 0;
}

void CTutorial_Stage::Late_Update(void)
{
	/*CTileMgr::Get_Instance()->Late_Update();*/
	CObjMgr::Get_Instance()->Late_Update();
	CLineMgr::Get_Instance()->Late_Update();
}	


void CTutorial_Stage::Render(HDC hDC)
{	
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Tutorial_Room");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC, iScrollX, iScrollY, 3500, 1969, hMemDC, 0, 0, SRCCOPY);
	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);
}

void CTutorial_Stage::Release(void)
{
	CObjMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Release();
}

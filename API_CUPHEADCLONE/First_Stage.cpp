#include "stdafx.h"
#include "First_Stage.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "KeyMgr.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "Root_Stage.h"
#include "Player.h"
#include "Player_UI.h"
#include "Press_Z.h"
#include "Bird.h"
#include "PinkBird.h"
#include "ButterFly.h"
#include "PinkButterFly.h"
#include "Dotori.h"
#include "Flower.h"
#include "FlyingMan.h"
#include "JumpEnemy.h"




CFirst_Stage::CFirst_Stage()
{
}


CFirst_Stage::~CFirst_Stage()
{
	Release();
}

void CFirst_Stage::Initialize(void)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(150.f, 800.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CPlayer_UI>::Create(70.f, 770.f));
	
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CPotato>::Create());
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Map/RunandGun/First_Map_1.bmp", L"First_Map");
	CLineMgr::Get_Instance()->Load_Line(L"../Data/Line_First.dat");

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CBird>::Create(7600.f, 200.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CBird>::Create(7300.f, 250.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CBird>::Create(6500.f, 250.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CBird>::Create(5900.f, 250.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CBird>::Create(5100.f, 250.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_PARRY, CAbstractFactory<CPinkBird>::Create(3700.f, 250.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_PARRY, CAbstractFactory<CPinkBird>::Create(2000.f, 250.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CButterFly>::Create(1500.f, 500.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_PARRY, CAbstractFactory<CPinkButterFly>::Create(1500.f, 500.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CButterFly>::Create(4800.f, 400.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_PARRY, CAbstractFactory<CPinkButterFly>::Create(4800.f, 500.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CDotori>::Create(1000.f, 500.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CDotori>::Create(1500.f, 500.f));


	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CFlower>::Create(2300.f, 530.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CFlower>::Create(6500.f, 830.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CFlower>::Create(4800.f, 500.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CFlyingMan>::Create(1000.f, 0.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CFlyingMan>::Create(7500.f, 0.f));
}

int CFirst_Stage::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CLineMgr::Get_Instance()->Update();




	return 0;
}

void CFirst_Stage::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
	CLineMgr::Get_Instance()->Late_Update();

	if (CObjMgr::Get_Instance()->Get_Player()->Get_HInfo().fX >= 900.f &&
		CObjMgr::Get_Instance()->Get_Player()->Get_HInfo().fX <= 1100.f)

	{
		if (!m_bIsFirst)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CPress_Z>::
				Create());
			m_bIsFirst = true;
		}
		if (CKeyMgr::Get_Instance()->Key_Down('Z'))
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_STAGEROOT);
		}
	}
		else
			m_bIsFirst = false;
	//m_iUICnt = 0;
}
	



void CFirst_Stage::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"First_Map");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC, iScrollX, iScrollY, 7500  , 1000  , hMemDC, 0, 0, SRCCOPY);
	CObjMgr::Get_Instance()->Render(hDC);
	//CLineMgr::Get_Instance()->Render(hDC);
}

void CFirst_Stage::Release(void)
{
	CObjMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Destroy_Instance();
}

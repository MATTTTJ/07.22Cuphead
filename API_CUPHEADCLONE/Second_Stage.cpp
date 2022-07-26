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
#include "DeadEventMgr.h"

#include "Root_Stage.h"
#include "Player.h"
#include "Player_UI.h"

#include "Sagittarius.h"
#include "Taurus.h"
#include "Star.h"
#include "Cloud.h"
#include "Cloud_Birth.h"

CSecond_Stage::CSecond_Stage()
{
	CDeadEventMgr::Get_Instance()->bind(&CSecond_Stage::CheckCloudDead, this);
}


CSecond_Stage::~CSecond_Stage()
{
	Release();
	CDeadEventMgr::Get_Instance()->unbind(this);
}

void CSecond_Stage::Initialize(void)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(200.f, 1700.f));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(5000.f, 1700.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CPlayer_UI>::Create(70.f, 770.f));

	m_CloudPoints[0] = tagFPoint(6600.f, 890.f);
	m_CloudPoints[1] = tagFPoint(6470.f, 1250.f);
	m_CloudPoints[2] = tagFPoint(6820.f, 1500.f);
	m_bCloudAlive[0] = true;
	m_bCloudAlive[1] = true;
	m_bCloudAlive[2] = true;
	m_dwCloudTimer[0] = GetTickCount();
	m_dwCloudTimer[1] = GetTickCount();
	m_dwCloudTimer[2] = GetTickCount();
	CObjMgr::Get_Instance()->Add_Object(OBJ_CLOUD, CAbstractFactory<CCloud>::Create(m_CloudPoints[0].fX, m_CloudPoints[0].fY));
	CObjMgr::Get_Instance()->Add_Object(OBJ_CLOUD, CAbstractFactory<CCloud>::Create(m_CloudPoints[1].fX, m_CloudPoints[1].fY));
	CObjMgr::Get_Instance()->Add_Object(OBJ_CLOUD, CAbstractFactory<CCloud>::Create(m_CloudPoints[2].fX, m_CloudPoints[2].fY));


	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CPotato>::Create());
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Map/Cloud/Cloud_Map_1.bmp", L"Cloud_Map");
	CLineMgr::Get_Instance()->Load_Line(L"../Data/Line_Second.dat");

}

int CSecond_Stage::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CLineMgr::Get_Instance()->Update();

	for (int i = 0; i < 3; ++i)
	{
		if (!m_bCloudAlive[i] && m_dwCloudTimer[i] + 3'000 < GetTickCount())
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CCloud_Birth>::Create(m_CloudPoints[i].fX, m_CloudPoints[i].fY));
			m_bCloudAlive[i] = true;
		}
	}

	return 0;
}

void CSecond_Stage::Late_Update(void)
{

	CObjMgr::Get_Instance()->Late_Update();
	CLineMgr::Get_Instance()->Late_Update();

	if (CObjMgr::Get_Instance()->Get_Player()->Get_HInfo().fX > 6000.f )
	{
		if (!m_bFirst_Sqawn)
		{
			//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CSagittarius>::Create(6500.f, 1500.f));
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTaurus>::Create(6600.f, 1100.f));
			//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CSagittarius>::Create(6600.f, 1300.f));
			CSoundMgr::Get_Instance()->PlayBGM(L"MUS_Stage_Second.wav", 0.8f);
			m_bFirst_Sqawn =true;
		}
	}
		
}

void CSecond_Stage::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Cloud_Map");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC, iScrollX, iScrollY, 7500, 2000, hMemDC, 0, 0, SRCCOPY);
	CObjMgr::Get_Instance()->Render(hDC);
	//CLineMgr::Get_Instance()->Render(hDC);
}

void CSecond_Stage::Release(void)
{
	CObjMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Release();
	CLineMgr::Get_Instance()->Destroy_Instance();
	CSoundMgr::Get_Instance()->StopAll();
//	CSoundMgr::Get_Instance()->Destroy_Instance();
}

void CSecond_Stage::CheckCloudDead(CObj* pCloud)
{
	tagFPoint ObjCloudPoint = tagFPoint(pCloud->Get_Info().fX, pCloud->Get_Info().fY);
	for (int i = 0; i < 3; ++i)
	{
		tagFPoint& tmp = m_CloudPoints[i];

		if (fabs(tmp.fX - ObjCloudPoint.fX) < EPSILON
			&& fabs(tmp.fY - ObjCloudPoint.fY) < EPSILON)
		{
			m_bCloudAlive[i] = false;
			m_dwCloudTimer[i] = GetTickCount();
			break;
		}
	}

	/*for (int i = 0; i < 3; ++i)
		m_bCloudAlive[i] = false;

	for (auto& pCloud : *CObjMgr::Get_Instance()->Get_ObjList(OBJ_CLOUD))
	{
		if (pCloud->Get_Dead()) continue;
		tagFPoint ObjCloudPoint = tagFPoint(pCloud->Get_Info().fX, pCloud->Get_Info().fY);
		for (int i = 0; i < 3; ++i)
		{
			tagFPoint& tmp = m_CloudPoints[i];

			if (fabs(tmp.fX - ObjCloudPoint.fX) < EPSILON
				&& fabs(tmp.fY - ObjCloudPoint.fY) < EPSILON)
			{
				m_bCloudAlive[i] = true;
				break;
			}
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		if (m_bCloudAlive[i] == false)
			m_dwCloudTimer[i] = GetTickCount();

		cout << i << " : " << m_bCloudAlive[i] << endl;
	}*/
}

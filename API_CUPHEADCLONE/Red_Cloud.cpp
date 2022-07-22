#include "stdafx.h"
#include "Red_Cloud.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Cloud.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "LineMgr.h"

CRed_Cloud::CRed_Cloud()
{
}


CRed_Cloud::~CRed_Cloud()
{
}

void CRed_Cloud::Initialize(void)
{
	CCloud::Initialize();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Taurus/Red_Cloud.bmp", L"Red_Cloud");
	m_pFrameKey = L"Red_Cloud";
}


void CRed_Cloud::Late_Update(void)
{
}



void CRed_Cloud::Release(void)
{
}

#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "ObjMgr.h"


CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Button/Start.bmp", L"Start");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Button/Edit.bmp", L"Edit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Button/Exit.bmp", L"Exit");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Title/Title_Screen_Background.bmp", L"Menu");

	CObj*	pObj = CAbstractFactory<CMyButton>::Create(200.f, 400.f);
	pObj->Set_FrameKey(L"Start");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(400.f, 400.f);
	pObj->Set_FrameKey(L"Edit");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(600.f, 400.f);
	pObj->Set_FrameKey(L"Exit");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pObj);

}

int CMyMenu::Update(void)
{
	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CMyMenu::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMyMenu::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Menu");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CMyMenu::Release(void)
{
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_BUTTON);
}

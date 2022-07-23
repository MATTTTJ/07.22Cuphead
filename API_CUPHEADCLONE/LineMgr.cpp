#include "stdafx.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;


CLineMgr::CLineMgr()
{
	ZeroMemory(m_tLinePoint, sizeof(m_tLinePoint));
}


CLineMgr::~CLineMgr()
{
	Release();
}

bool CLineMgr::Collision_Line(float& fX, float& fY, float* pY)
{
	if (m_LineList.empty())
		return false;

	bool bCheck = true;

	float fHighest_Y = 0.f;

	for (auto& iter : m_LineList)
	{
		if (fX >= iter->Get_LineInfo().tLeftPt.fX  &&
			fX <= iter->Get_LineInfo().tRightPt.fX)
		{
			float x1 = iter->Get_LineInfo().tLeftPt.fX;
			float x2 = iter->Get_LineInfo().tRightPt.fX;
			float y1 = iter->Get_LineInfo().tLeftPt.fY;
			float y2 = iter->Get_LineInfo().tRightPt.fY;

			float fCheck_Y = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;

			if ((fCheck_Y >= fY) && (fHighest_Y > fCheck_Y) || (bCheck && fCheck_Y >= fY))
			{
				fHighest_Y = fCheck_Y;
				bCheck = false;
			}
		}
	}

	if (!bCheck)
	{
		*pY = fHighest_Y;
		return true;
	}

	return false;


}

void CLineMgr::Save_Line(void)
{
	HANDLE		hFile = CreateFile(L"../Data/Line.dat",		// ������ ��ο� �̸�
									GENERIC_WRITE,			// ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
									NULL,					// ���� ���(������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�)	 
									NULL,					// ���� �Ӽ�(NULL�� �����ϸ� �⺻�� ����)
									CREATE_ALWAYS,			// CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING  : ������ ���� ��쿡�� ����
									FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ��) : FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� ����
									NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ��ϱ� NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte = 0;

	for (auto& iter : m_LineList)
		WriteFile(hFile, &(iter->Get_LineInfo()), sizeof(LINE), &dwByte, nullptr);

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save �Ϸ�"), L"Success", MB_OK);
}

void CLineMgr::Load_Line(const TCHAR* _szFileName)
{

	HANDLE		hFile = CreateFile(_szFileName,		// ������ ��ο� �̸�
		GENERIC_READ,			// ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
		NULL,					// ���� ���(������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�)	 
		NULL,					// ���� �Ӽ�(NULL�� �����ϸ� �⺻�� ����)
		OPEN_EXISTING,			// CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING  : ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ��) : FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� ����
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ��ϱ� NULL)
	//HANDLE		hFile = CreateFile(L"../Data/Line.dat",		// ������ ��ο� �̸�
	//	GENERIC_READ,			// ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
	//	NULL,					// ���� ���(������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�)	 
	//	NULL,					// ���� �Ӽ�(NULL�� �����ϸ� �⺻�� ����)
	//	OPEN_EXISTING,			// CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING  : ������ ���� ��쿡�� ����
	//	FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ��) : FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� ����
	//	NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ��ϱ� NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte = 0;

	LINE	tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo));
	}
	

	CloseHandle(hFile);

	//MessageBox(g_hWnd, _T("Load �Ϸ�"), L"Success", MB_OK);

}

void CLineMgr::Initialize(void)
{
	//Load_Line();
}

int CLineMgr::Update(void)
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		// ���콺 Ŭ���� ó�� ���� ��(�ƿ� ���� ���� ��)
		if ((!m_tLinePoint[LEFT].fX) && (!m_tLinePoint[LEFT].fY))
		{
			m_tLinePoint[LEFT].fX = (float)pt.x;
			m_tLinePoint[LEFT].fY = (float)pt.y;
		}

		else
		{
			m_tLinePoint[RIGHT].fX = (float)pt.x;
			m_tLinePoint[RIGHT].fY = (float)pt.y;

			LINE	tInfo{ m_tLinePoint[0], m_tLinePoint[1] };
			m_LineList.push_back(new CLine(tInfo));

			m_tLinePoint[LEFT].fX = m_tLinePoint[RIGHT].fX;
			m_tLinePoint[LEFT].fY = m_tLinePoint[RIGHT].fY;
		}

	}
	
	return 0;
}

void CLineMgr::Late_Update(void)
{

}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(hDC);
}

void CLineMgr::Release(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();
}

void CLineMgr::Create_Line_Cloud(void)
{
	/*CLOUDPOINT	tCloudLinePt[2] = {
		{ (float)m_HRect.left , m_HInfo.fY },
		{ (float)m_HRect.right, m_HInfo.fY }
	};

	m_LineList->push_back(new CLine(tCloudLinePt[0], tCloudLinePt[1]));
}*/
}

void CLineMgr::Delete_Line_Cloud(CLine & ToDeleteLine)
{
	for (auto iter = m_LineList.begin(); iter != m_LineList.end(); )
	{
		CLine* TmpLine = (*iter);

		if (TmpLine->Get_LineInfo() == ToDeleteLine.Get_LineInfo())
		{
			Safe_Delete<CLine*>(*iter);
			iter = m_LineList.erase(iter);
		}
		else
			++iter;
	}
}

#pragma once

#include "Line.h"
#include "Wall.h"
class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	bool		Collision_Line(float& fX,float& fY, float* pY);

	void		Save_Line(void);
	void		Load_Line(const TCHAR* _szFileName);


public:
	void		Initialize(void);
	int			Update(void);
	void		Late_Update(void);

	void		Render(HDC hDC);
	void		Release(void);
	
public:
	static CLineMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CLineMgr;

		return m_pInstance;
	}
	static void		Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	LINEPOINT				m_tLinePoint[END];
	static CLineMgr*		m_pInstance;
	list<CLine*>			m_LineList;

	list<CWall*>			m_WallList;
};


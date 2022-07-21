#pragma once
#include "Obj.h"
class CWall :
	public CObj
{
public:
	CWall();
	CWall(POINT _pt);
	CWall(INFO _tInfo);
	virtual ~CWall();

public:

	virtual void Initialize(void) override;
	virtual int Update(void)		override;
	virtual void Render(HDC hDC) override;
	virtual void	Late_Update(void)override {}

	virtual void Release(void) override;

	const INFO& Get_WallInfo(void) const { return m_tInfo; }


	void			Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void			Set_PosY(float _fY) { m_tInfo.fY += _fY; }

	void Set_Pos(POINT _pt)
	{
		m_tInfo.fX = (float)_pt.x;
		m_tInfo.fY = (float)_pt.y;
	}

	void Set_CX(float _fCX)
	{
		m_tInfo.fCX += _fCX;
	}
	void Set_CY(float _fCY)
	{
		m_tInfo.fCY += _fCY;
	}

	bool m_bSelected = false;
};


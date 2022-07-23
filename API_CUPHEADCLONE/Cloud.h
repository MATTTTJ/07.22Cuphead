#pragma once
#include "Monster.h"
#include "Line.h"
#include "LineMgr.h"

typedef list<CLine*>		LINELIST;


class CCloud :
	public CObj
{
public:
	CCloud();
	virtual ~CCloud();


	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual void Creat_Line_Cloud(void);

private:
	list<CLine*>*	m_pLineList;

};


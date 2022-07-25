#pragma once
#include "Scene.h"
class CMyMenu :
	public CScene
{
public:
	CMyMenu();
	virtual ~CMyMenu();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	void Move_Frame(void);

private:
	FRAME		m_tFrame;
};


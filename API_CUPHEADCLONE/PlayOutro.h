#pragma once
#include "Scene.h"
class CPlayOutro :
	public CScene
{
public:
	CPlayOutro();
	virtual ~CPlayOutro();


public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	HWND		m_hVideo;



};


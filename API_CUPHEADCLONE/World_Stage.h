#pragma once
#include "Scene.h"
#include "Obj.h"

class CWorld_Stage :
	public CScene
{
public:
	CWorld_Stage();
	virtual ~CWorld_Stage();
	
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	CObj* Create_Wall(float _fX, float _fY);
};


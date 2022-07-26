#pragma once
#include "Scene.h"
#include "Obj.h"

struct tagFPoint
{
	float fX;
	float fY;
	tagFPoint() : fX(0.f), fY(0.f) {}
	tagFPoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}
};

class CSecond_Stage :
	public CScene
{
public:
	CSecond_Stage();
	virtual ~CSecond_Stage();

public:
	virtual void Initialize(void) override;
	virtual int	Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void CheckCloudDead(CObj* pCloud);


private:
	bool	m_bFirst_Sqawn = false;

	float	m_fWallaVol;
	tagFPoint m_CloudPoints[3];
	bool m_bCloudAlive[3];
	DWORD m_dwCloudTimer[3];
};


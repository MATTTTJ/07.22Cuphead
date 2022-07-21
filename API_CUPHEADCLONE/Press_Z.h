#pragma once
#include "Obj.h"
#include "ObjTimer.h"

class CPress_Z :
	public CObj
{
public:
	CPress_Z();
	virtual ~CPress_Z();


	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	void		 Update_Info(void);

private:
	CObj*		pPlayer;


	CObjTimer	Ani_Change_Timer;
	bool		m_bIsRed = false;
};


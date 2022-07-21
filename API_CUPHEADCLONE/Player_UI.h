#pragma once
#include "Obj.h"
#include "ObjTimer.h"
class CPlayer_UI :
	public CObj
{
public:
	CPlayer_UI();
	virtual ~CPlayer_UI();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	
private:
	CObj*		pPlayer;

	//타이머 오류남 도대체 왜 ?
	CObjTimer	Ani_Change_Timer;
	bool		m_bIsRed = false;

};


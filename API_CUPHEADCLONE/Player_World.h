#pragma once
#include "Obj.h"
class CPlayer_World :
	public CObj
{
	enum WPSTATE { IDLE, WALK, END };
public:
	CPlayer_World();
	virtual ~CPlayer_World();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		Offset(void);

private:
	void		Key_Input(void);
	void		Motion_Change(void);

	WPSTATE			m_ePreState;
	WPSTATE			m_eCurState;

	LOOK			m_eLookState;
};


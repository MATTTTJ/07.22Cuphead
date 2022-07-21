#pragma once
#include "Scene.h"
class CFirst_Stage :
	public CScene
{
public:
	CFirst_Stage();
	virtual ~CFirst_Stage();


public:
	virtual void Initialize(void) override;
	virtual int	Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	void	Minus_BirdCnt(void) { m_iBirdCnt -= 1; }
private:
	int		m_iBirdCnt = 0;
	int		m_iBirdMaxCnt = 6;
	bool	m_bIsFirst = false;

	int		m_iUICnt = 0;
	int		m_iUIMaxCnt = 1;

	DWORD	m_JumpE_Sqawn_One = GetTickCount();

	DWORD	m_JumpE_Sqawn_Two = GetTickCount();

	DWORD	m_Bird_SqawnTimer = GetTickCount();

	DWORD	m_Pink_Bird_SqawnTimer = GetTickCount();
	
	DWORD	m_FlyingMan_SqawnTimer = GetTickCount();
};


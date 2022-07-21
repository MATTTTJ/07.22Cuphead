#pragma once
#include "Scene.h"
class CRoot_Stage :
	public CScene
{
public:
	CRoot_Stage();
	virtual ~CRoot_Stage();

public:
	virtual void Initialize(void) override;
	virtual int	Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	bool	m_bIsPotatoDead = false;
	bool	m_bIsOnionDead = false;
	bool	m_bIsCarrotDead = false;
};


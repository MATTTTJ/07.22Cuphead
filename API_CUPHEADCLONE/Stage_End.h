#pragma once
#include "Scene.h"
class CStage_End :
	public CScene
{
public:
	CStage_End();
	virtual ~CStage_End();

public:
	virtual void Initialize(void) override;
	virtual int	Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	void		 Move_Frame(void);
private:
	FRAME	m_tFrame;

	DWORD	m_dwEndTime;
};


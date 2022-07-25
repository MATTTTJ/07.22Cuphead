#pragma once

#include "Include.h"

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	float		Get_ScrollX(void) { return m_fScrollX; }
	void		Set_ScrollX(float _fX) { m_fScrollX += _fX; }

	float		Get_ScrollY(void) { return m_fScrollY; }
	void		Set_ScrollY(float _fY) { m_fScrollY += _fY; }

	void		Scroll_Lock(void);
	void		Update(void);
	void		Shake();
public:
	static CScrollMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CScrollMgr;

		return m_pInstance;
	}
	static void		Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}


private:
	bool m_bScrollShake = true;
	int m_iShakeCnt = 6;
	int m_iShakeMaxCnt = 6 ;
	DWORD m_dwShaketimer;


	static CScrollMgr*		m_pInstance;
	float					m_fScrollX;
	float					m_fScrollY;
	
	SCENEID					m_eCurScene;


};



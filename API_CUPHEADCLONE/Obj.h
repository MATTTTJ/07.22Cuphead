#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY) 
	{ 
		m_tInfo.fX = _fX; 
		m_tInfo.fY = _fY;

		m_HInfo.fX = _fX;
		m_HInfo.fY = _fY;
	}

	void		Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void		Set_tPosY(float _fY) { m_tInfo.fY = _fY; }
	void		Set_hPosY(float _fY) { m_HInfo.fY = _fY; }

	void		Set_Dir(DIR eDir)			{ m_eDir = eDir; }
	void		Set_Angle(float _fAngle)	{ m_fAngle = _fAngle; }

	void		Set_Target(CObj* _pTarget)  { m_pTarget = _pTarget; }
	void		Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }
	
	const RECT&			Get_Rect(void) const { return m_tRect; }

	const RECT&			Get_HRect(void) const { return m_HRect; }

	const INFO&			Get_Info(void) const { return m_tInfo; }

	const INFO&			Get_HInfo(void) const { return m_HInfo; }

	const PLAYERINFO&	Get_PInfo(void) const { return m_tStat; }
	

	void			Kill_Obj(void) { m_bDead = true; }
	bool			Get_Dead(void) { return m_bDead; }

	const RENDERID	Get_RenderID(void) const { return m_eRenderGroup; }

public:
	virtual void	Initialize(void)						PURE;
	virtual int		Update(void)							PURE;
	virtual void	Late_Update(void)						PURE;
	virtual void	Render(HDC hDC)							PURE;
	virtual void	Release(void)							PURE;
	virtual	void	Collision_Event(CObj* _OtherObj,float _fColX, float _fColY) {}

protected:
	void			Update_Rect(void);
	void			Move_Frame(int _InitFrame = 0);


protected:
	INFO		m_tInfo;
	INFO		m_HInfo;
	PLAYERINFO	m_tStat;
	RECT		m_tRect;
	RECT		m_HRect;

	FRAME		m_tFrame;

	DIR			m_eDir;

	float		m_fSpeed = 0.f;
	float		m_fAngle = 0.f;
	float		m_fDiagonal = 0.f;
	float		m_iAnimationCount = 0.f;
	POINT		m_tPosin;

	bool		m_bDead;
	CObj*		m_pTarget;
	CObj*		m_MTarget;
	RENDERID	m_eRenderGroup;

	TCHAR*		m_pFrameKey;

	list<CObj*>		m_ObjList[OBJ_END];

	bool m_bScrollShake = true;
	int m_iShakeCnt = 10;
	int m_iShakeMaxCnt = 10;
	DWORD m_dwShaketimer;

};


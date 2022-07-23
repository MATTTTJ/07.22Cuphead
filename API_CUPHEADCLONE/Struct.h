#pragma once

typedef struct tagInfo
{
	float	fX;
	float	fY;
	float	fCX;
	float	fCY;

	float	m_fDamage;

}INFO;

typedef struct tagPlayer
{
	float	fHp;
	float	fMaxHp;
	float	fDamage;
}PLAYERINFO;

typedef struct tagPoint
{
	float	fX;
	float	fY;

	tagPoint(void) { ZeroMemory(this, sizeof(tagPoint)); }
	tagPoint(float _fX, float _fY)
		: fX(_fX), fY(_fY)
	{

	}

}LINEPOINT, CLOUDPOINT;

typedef struct tagLine
{
	LINEPOINT		tLeftPt;
	LINEPOINT		tRightPt;

	tagLine(void) {	ZeroMemory(this, sizeof(tagLine)); }
	tagLine(LINEPOINT& _tLeftPt, LINEPOINT& _tRightPt)
		: tLeftPt(_tLeftPt), tRightPt(_tRightPt)
	{

	}

	bool operator==	(const tagLine& rhs) const
	{
		return tLeftPt.fX == rhs.tLeftPt.fX && tLeftPt.fY == rhs.tLeftPt.fY
			&& tRightPt.fX == rhs.tRightPt.fX && tRightPt.fY == rhs.tRightPt.fY;
	}

}LINE;

typedef	struct	tagFrame 
{
	int		iFrameStart;
	int		iFrameEnd;
	int		iMotion;

	DWORD	dwFrameSpeed;
	DWORD	dwFrameTime;


}FRAME;
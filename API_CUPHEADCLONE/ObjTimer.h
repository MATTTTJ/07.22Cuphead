#pragma once

enum TIMER_TYPE
{
	LOOP,
	TICK
};

class CObjTimer
{
public:
	CObjTimer();
	virtual ~CObjTimer();

	virtual void InitLoop(float _fTick)
	{
		m_eType = LOOP;
		m_dwTickTime = GetTickCount();
		m_fTick = _fTick;
	}

	virtual void InitTick(float _fTime, float _fTick = 0.f)
	{
		m_eType = TICK;
		m_dwTickTime = GetTickCount(); // Question
		m_fTime = _fTime; // 
		m_fTick = _fTick; //
		Reset();
	}

	virtual bool Check();

	// for TICK type
	virtual void Reset()
	{
		m_dwLastTime = GetTickCount() +DWORD( m_fTime * 1000);
	}

private:
	TIMER_TYPE m_eType = LOOP;

	float m_fTime; // sec
	DWORD m_dwLastTime;

	float m_fTick;
	DWORD m_dwTickTime;
};


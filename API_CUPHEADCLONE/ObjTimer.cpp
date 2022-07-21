#include "stdafx.h"
#include "ObjTimer.h"


CObjTimer::CObjTimer()
{
}


CObjTimer::~CObjTimer()
{
}

bool CObjTimer::Check()
{
	if (m_eType == LOOP)
	{
		if (m_dwTickTime + (m_fTick * 1000) < GetTickCount())
		{
			m_dwTickTime = GetTickCount();
			return true;
		}

		return false;
	}
	else
	{
		if (m_dwLastTime > GetTickCount())
		{
			if (m_dwTickTime + (m_fTick * 1000) < GetTickCount())
			{
				m_dwTickTime = GetTickCount();
				return true;
			}
		}
		return false;
	}
}

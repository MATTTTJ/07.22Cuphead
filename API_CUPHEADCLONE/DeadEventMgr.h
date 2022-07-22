#pragma once
#include <functional>
#include "Obj.h"

class CDeadEventMgr
{
private:
	CDeadEventMgr();
	virtual ~CDeadEventMgr();
	typedef std::function<void(CObj*)> bindtype;

public:
	static CDeadEventMgr* Get_Instance()
	{
		static CDeadEventMgr Instance;
		return &Instance;
	}

public:
	void broadcast(CObj* pCloud)
	{
		for (auto d : m_vecBinds)
			d.second(pCloud);
	}
	template<typename T>
	void bind(void(T::*method)(CObj*), T* obj) //브로드캐스트가 실행됐을 때 이 (위임된)함수를 실행해주세요. 하는 함수 
	{
		m_vecBinds.push_back(std::make_pair(obj, std::bind(method, obj, std::placeholders::_1)));
	}

	template<typename T>
	void unbind(T* obj) // 
	{
		auto removedItr = remove_if(m_vecBinds.begin(), m_vecBinds.end(),
			[&obj](std::pair<void*, bindtype>& e) { return e.first == obj; }
		);
		m_vecBinds.erase(removedItr, m_vecBinds.end());
	}

private:
	std::vector<std::pair<void*, bindtype>> m_vecBinds;


};

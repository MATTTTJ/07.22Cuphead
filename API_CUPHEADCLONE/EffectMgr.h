#pragma once

#include "Effect.h"


class CEffectMgr
{
public:
	CEffectMgr();
	~CEffectMgr();

public:
	void		Add_Object(OBJID eID, CObj* pObj);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	void		Delete_OBJID(OBJID eID);

public:
	CObj*			Get_Player() { return m_ObjList[OBJ_PLAYER].front(); }
	list<CObj*>*	Get_ObjList(OBJID eID) { return &m_ObjList[eID]; }
	CObj*			Get_Target(OBJID eID, CObj* pObj);


public:
	static CEffectMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CEffectMgr;

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
	static CEffectMgr*		m_pInstance;

	list<CObj*>		m_ObjList[OBJ_END];
	list<CObj*>		m_RenderSort[RENDER_END];


};


#pragma once

#include "Obj.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

	//CObjMgr(const CObjMgr& rhs)				= delete;	// default 복사 생성자
	//CObjMgr& operator=(const CObjMgr& rhs)  = delete;	// default 대입 연산자

public:
	void		Add_Object(OBJID eID, CObj* pObj);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	void		Delete_OBJID(OBJID eID);

public:
	CObj*			Get_Player() { return m_ObjList[OBJ_PLAYER].front();  }
	CObj*			Get_PlayerWorld() { return m_ObjList[OBJ_PLAYER_WORLD].front(); }
	list<CObj*>*	Get_ObjList(OBJID eID){	return &m_ObjList[eID];	}
	CObj*			Get_Target(OBJID eID, CObj* pObj);
	void		    Shake_Window(void);
	

public:
	static CObjMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;

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
	static CObjMgr*		m_pInstance;

	list<CObj*>		m_ObjList[OBJ_END];
	list<CObj*>		m_RenderSort[RENDER_END];

protected:
	bool m_bScrollShake = true;
	int m_iShakeCnt = 6;
	int m_iShakeMaxCnt = 6;
	DWORD m_dwShaketimer;
};


#include "stdafx.h"
#include "EffectMgr.h"

CEffectMgr* CEffectMgr::m_pInstance = nullptr;

CEffectMgr::CEffectMgr()
{
}


CEffectMgr::~CEffectMgr()
{
	Release();
}

void CEffectMgr::Add_Object(OBJID eID, CObj * pObj)
{
	if (OBJ_END <= eID || nullptr == pObj)
		return;

	m_ObjList[eID].push_back(pObj);
}

int CEffectMgr::Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return 0;
}

void CEffectMgr::Late_Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& Obj : m_ObjList[i])
		{
			Obj->Late_Update();

			if (m_ObjList[i].empty())
				break;

			RENDERID		eID = Obj->Get_RenderID();
			m_RenderSort[eID].push_back(Obj);
		}
	}
}

void CEffectMgr::Render(HDC hDC)
{
	for (int i = 0; i < RENDER_END; ++i)
	{
		m_RenderSort[i].sort(CompareY<CObj*>);

		for (auto& Obj : m_RenderSort[i])
			Obj->Render(hDC);

		m_RenderSort[i].clear();
	}
}

void CEffectMgr::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
}

void CEffectMgr::Delete_OBJID(OBJID eID)
{
	for (auto& iter : m_ObjList[eID])
		Safe_Delete(iter);

	m_ObjList[eID].clear();
}

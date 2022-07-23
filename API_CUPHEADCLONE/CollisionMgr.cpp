#include "stdafx.h"
#include "CollisionMgr.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}			
									//   총알					보스
void CCollisionMgr::Collision_HRect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT	rc{};
	float fX = 0.f;
	float fY = 0.f;
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (IntersectRect(&rc, &(Dest->Get_HRect()), &(Sour->Get_HRect())))
			{
				Dest->Collision_Event(Sour, fX, fY);
				Sour->Collision_Event(Dest, fX, fY);
			}
		}
	}
}


void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT	rc{};
	float fX = 0.f;
	float fY = 0.f;
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Rect(Dest,Sour, &fX, &fY))
			{
				Dest->Collision_Event(Sour, fX, fY);
				Sour->Collision_Event(Dest, fX, fY);
			}
		}
	}
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{
				Dest->Kill_Obj();
				Sour->Kill_Obj();
			}
		}
	}
}
									 //   충돌하는 대상			장애물
void CCollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			float		fX = 0.f, fY = 0.f;

			if (Check_HRect(Dest, Sour, &fX, &fY))
			{
				// 상.하 충돌
				if (fX > fY)
				{
					// 하 충돌
					//if (Dest->Get_Info().fY > Sour->Get_Info().fY)
					//	Dest->Set_PosY(fY);

					//// 상 충돌
					//else
					if (Dest->Get_HInfo().fY < Sour->Get_HInfo().fY)
					{
						Dest->Set_tPosY(Sour->Get_HInfo().fY);
					}
				}

				// 좌.우 충돌
				//else
				//{
				//	// 우 충돌
				//	if (Dest->Get_Info().fX > Sour->Get_Info().fX)
				//		Dest->Set_PosX(fX);

				//	// 좌 충돌
				//	else
				//		Dest->Set_PosX(-fX);
				}
			}
		}
	}


bool CCollisionMgr::Check_Rect(CObj * pDest, CObj * pSour, float * pX, float * pY)
{
	float		fWidth  = abs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float		fHeight = abs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	float		fRadiusX = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;
	float		fRadiusY = (pDest->Get_Info().fCY + pSour->Get_Info().fCY) * 0.5f;

	if ((fWidth < fRadiusX) && (fHeight < fRadiusY))
	{
		*pX	= fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}


	return false;
}

bool CCollisionMgr::Check_HRect(CObj * pDest, CObj * pSour, float * pX, float * pY)
{
	float		fWidth = abs(pDest->Get_HInfo().fX - pSour->Get_HInfo().fX);
	float		fHeight = abs(pDest->Get_HInfo().fY - pSour->Get_HInfo().fY);

	float		fRadiusX = (pDest->Get_HInfo().fCX + pSour->Get_HInfo().fCX) * 0.5f;
	float		fRadiusY = (pDest->Get_HInfo().fCY + pSour->Get_HInfo().fCY) * 0.5f;

	if ((fWidth < fRadiusX) && (fHeight < fRadiusY))
	{
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}


	return false;
}

bool CCollisionMgr::Check_Sphere(CObj* pDest, CObj* pSour)
{
	// c^2 = a^2 + b^2

	// fabs : 절대값을 구해주는 함수
	float	fWidth  = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float	fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	// sqrtf : 루트를 씌워 값을 구해주는 함수
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;
	
	return fRadius >= fDiagonal;
}

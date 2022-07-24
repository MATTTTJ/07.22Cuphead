#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"
#include "EffectMgr.h"
#include "Bullet_Effect.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "Potato.h"
#include "Potato_Bullet.h"
#include "BmpMgr.h"
#include "Carrot_Bullet.h"
#include "Potato_Parry_Bullet.h"
#include "Onion_Parry_Bullet.h"
#include "SceneMgr.h"
#include "Parry_Effect.h"
#include "Land_Effect.h"
#include "Hit_Effect.h"	
#include "Dash_Effect.h"
#include "Player_Dust.h"
#include "PinkBird.h"
#include "PinkButterFly.h"
#include "Dotori.h"
#include "FlyingMan.h"
#include "JumpEnemy.h"
#include "Flower.h"
#include "Taurus.h"
#include "Sagittarius.h"
#include "Arrow.h"
#include "BasicBullet.h"
CPlayer::CPlayer()
	: m_eCurState(IDLE), m_ePreState(MOTION_END), m_eLookState(LOOK_RIGHT)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fCX = 280.f;
	m_tInfo.fCY = 280.f;


	m_HInfo = { m_tInfo.fX, m_tInfo.fY, 80.f, 115.f };


	m_tStat.fMaxHp = 8.f;
	m_tStat.fHp = m_tStat.fMaxHp;
	m_tStat.fDamage = 1.f;

	m_fSpeed = 7.f;
	m_fDiagonal = 100.f;
	m_iSpecial_Gauge = 0.f;


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Player_Right_All.bmp", L"Player_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Player_Left_All.bmp", L"Player_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Player_Dash.bmp", L"Player_Dash");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Player_Right_Dash.bmp", L"Player_Right_Dash");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Hit.bmp", L"Hit");
	m_pFrameKey = L"Player_Right";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_fDashSpeed = m_fSpeed * 1.8f;
	m_dwDustTime = GetTickCount();


	m_bDefault_Bullet = true;
	m_bBounce_Bullet = false;

	m_bDash = false;

	m_eRenderGroup = GAMEOBJECT;

	m_dwHitTime = GetTickCount();
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;



	if (m_bIsHit && m_dwHitTime + 500 < GetTickCount())
	{
		m_bIsHit = false;
		m_eCurState = IDLE;
	}

	Key_Input();
	Shoot_Hor();
	Shoot_DIR();
	Run_Shoot_Hor();
	Parry();
	Ground_Check();
	Dash();
	Update_Parry();
	Motion_Change();
	Move_Frame();
	Offset();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Ground_Check(void)
{




	m_bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_HInfo.fX, m_HInfo.fY, &m_fFootY);


	/*if (m_eLookState == LOOK_RIGHT)
	{
		if ((m_fPreFootY < m_fFootY))
			m_eState = FALL;

	}
	else if(m_eLookState == LOOK_LEFT)
	{
		if ((m_fPreFootY > m_fFootY))
			m_eState = FALL;
	}*/
	if (m_fFootY != m_fPreFootY)
	{
		if (m_eState == GROUND && m_fFootY - m_fPreFootY > 10.f)
		{
			m_eState = FALL;
			m_bJump = true;
			m_fCurJumpSpeed = 0;
		}
	}

	m_fPreFootY = m_fFootY;
	///*if (!m_bLineCol)
	//{
	//	
	//}*/

	//if (m_eState != m_ePreState22)
	//{

	//	switch (m_eState)
	//	{
	//	case AIR:
	//		cout << "AIR" << endl;

	//		break;
	//	case GROUND:
	//		cout << "GROUND " << endl;

	//		break;
	//	case FALL:
	//		cout << "FALL :" << endl;
	//		break;
	//	}
	//	m_ePreState22 = m_eState;
	//}





	//if ((m_fPreFootY < m_fFootY && m_eState != GROUND)) //|| m_fPreFootY > m_fFootY))
	//	m_eState = FALL;
	//else if (m_fPreFootY > m_fFootY && m_eState != GROUND)
	//	m_eState = FALL;


	float fCurFootY = m_HInfo.fY + m_HInfo.fCY * 0.5f;

	switch (m_eState)
	{
	case AIR:
		if (m_bIsHit || m_bDash) break;

		m_tInfo.fY -= m_fCurJumpSpeed;
		m_HInfo.fY -= m_fCurJumpSpeed;


		if (fabs(m_fCurJumpSpeed) < m_fMaxAbsJumpSpeed) // limit max speed
		{
			m_fCurJumpSpeed -= GRAVITY;
			m_bJump = true;
			m_bGround = true;

			if (!m_bIsParry)
				m_eCurState = JUMP;
			else
				m_eCurState = PARRY;
		}
		break;
	case GROUND:
		m_fCurJumpSpeed = 0.f;
		m_HInfo.fY = m_fFootY - m_HInfo.fCY * 0.5f;
		m_tInfo.fY = m_fFootY - m_tInfo.fCY * 0.5f;
		m_bJump = false;
		m_bIsParry = false;
		break;

	case FALL:
		if (m_bIsHit || m_bDash) break;

		m_tInfo.fY -= m_fCurJumpSpeed;
		m_HInfo.fY -= m_fCurJumpSpeed;
		if (fabs(m_fCurJumpSpeed) < m_fMaxAbsJumpSpeed) // limit max speed
		{
			m_fCurJumpSpeed -= GRAVITY;
			m_eCurState = JUMP;
		}
		break;

	default:
		break;
	}



	if (m_eState == GROUND && m_eCurState == RUN && m_eLookState == LOOK_LEFT)
	{
		if (m_dwDustTime + 250 < GetTickCount())
		{
			CObj* pPlayer_Dust = CAbstractFactory<CPlayer_Dust>::Create((float)m_HRect.right, m_HInfo.fY);
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, pPlayer_Dust);
			m_dwDustTime = GetTickCount();
		}
	}
	else if (m_eState == GROUND && m_eCurState == RUN && m_eLookState == LOOK_RIGHT)
	{
		if (m_dwDustTime + 250 < GetTickCount())
		{
			CObj* pPlayer_Dust = CAbstractFactory<CPlayer_Dust>::Create((float)m_HRect.left, m_HInfo.fY);
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, pPlayer_Dust);
			m_dwDustTime = GetTickCount();
		}
	}

	if (m_bIsHit)
		m_eCurState = HIT;

	fCurFootY = m_HInfo.fY + m_HInfo.fCY * 0.5f;


	if (m_bLineCol && abs(m_fFootY - fCurFootY) < m_fMaxAbsJumpSpeed * 0.5f)
	{
		m_eState = GROUND;

		if (m_bGround)
		{
			CObj* pLand_Effect = CAbstractFactory<CLand_Effect>::Create(m_HInfo.fX, (float)m_HRect.bottom);
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, pLand_Effect);
			m_bGround = false;


		}
	}
	else
		m_eState = AIR;


}

void CPlayer::Update_Parry(void)
{
	if (m_bParryShake)
	{
	}
	if (m_bParryShake && m_eCurState == PARRY && m_bScrollShake && m_iShakeCnt < m_iShakeMaxCnt && m_dwShaketimer + 20 < GetTickCount())
	{
		float fShakeMount = m_iShakeCnt % 2 == 0 ? -10.f : 10.f;
		CScrollMgr::Get_Instance()->Set_ScrollX(fShakeMount);
		m_dwShaketimer = GetTickCount();
		++m_iShakeCnt;

		if (m_iShakeCnt >= m_iShakeMaxCnt)
		{
			CSoundMgr::Get_Instance()->PlaySounD(L"sfx_player_parry_slap_01.wav", SOUND_EFFECT, 1.f);
			cout << "A" << endl;

			m_bParryShake = false;
		}
	}

}



void CPlayer::Late_Update(void)
{
#ifdef _DEBUG

	//system("cls");
	//cout << "플레이어 좌표 : " << m_tInfo.fX << "\t" << m_tInfo.fY << endl;

#endif // _DEBUG	

}

void CPlayer::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,	// 복사 받을 위치의 좌표 전달(x,y 순서)
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,		// 복사 받을 이미지의 길이 전달(가로, 세로순서)
		(int)m_tInfo.fCY,
		hMemDC,					// 비트맵을 가지고 있는 dc
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,						// 출력할 비트맵 시작 좌표(x,y 순서)
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,			// 복사 할 비트맵 의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(1, 1, 1));	// 제거할 픽셀의 색상


//	Rectangle(hDC, m_HRect.left + iScrollX, m_HRect.top + iScrollY, m_HRect.right + iScrollX, m_HRect.bottom + iScrollY);
}

void CPlayer::Release(void)
{

}

void CPlayer::Collision_Event(CObj * _OtherObj, float _fColX, float _fColY)
{

	if (m_bIsHit) return;

	CBullet* pBullet = dynamic_cast<CBullet*>(_OtherObj);
	if (pBullet)
	{
		m_tStat.fHp -= pBullet->Get_Damage();

		m_bIsHit = true;
		m_dwHitTime = GetTickCount();
		m_eCurState = HIT;
	}

	CPotato_Parry_Bullet* pParryBullet = dynamic_cast<CPotato_Parry_Bullet*>(_OtherObj);
	if (pParryBullet)
	{
		if (m_bIsParry)
		{
			m_iSpecial_Gauge += 1.f;
			m_fCurJumpSpeed = m_fInitJumpSpeed;
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CParry_Effect>::Create(m_tInfo.fX, (float)m_HRect.bottom));
			m_bParryShake = true;
		}
		else
		{
			m_tStat.fHp -= pParryBullet->Get_Damage();

			m_bIsHit = true;
			m_dwHitTime = GetTickCount();
			m_eCurState = HIT;
		}
	}

	CPinkButterFly* pParryBF = dynamic_cast<CPinkButterFly*>(_OtherObj);
	if (pParryBF)
	{
		if (m_bIsParry)
		{
			m_iSpecial_Gauge += 1.f;
			m_fCurJumpSpeed = m_fInitJumpSpeed;
			pParryBF->Kill_Obj();
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CParry_Effect>::Create(m_tInfo.fX, (float)m_HRect.bottom));
			m_bParryShake = true;
		}
	}

	CPinkBird* pParryBird = dynamic_cast<CPinkBird*>(_OtherObj);
	if (pParryBird)
	{
		if (m_bIsParry)
		{
			m_iSpecial_Gauge += 1.f;
			m_fCurJumpSpeed = m_fInitJumpSpeed;
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CParry_Effect>::Create(m_tInfo.fX, (float)m_HRect.bottom));
			pParryBird->Kill_Obj();
			m_bParryShake = true;
		}
		else
		{
			m_tStat.fHp -= pParryBird->Get_Damage();
			pParryBird->Kill_Obj();
			m_bIsHit = true;
			m_dwHitTime = GetTickCount();
			m_eCurState = HIT;
		}
	}

	COnion_Parry_Bullet* pOParryBullet = dynamic_cast<COnion_Parry_Bullet*>(_OtherObj);
	if (pOParryBullet)
	{
		if (m_bIsParry)
		{
			m_iSpecial_Gauge += 1.f;
			m_fCurJumpSpeed = m_fInitJumpSpeed;
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CParry_Effect>::Create(m_tInfo.fX, (float)m_HRect.bottom));
			m_bParryShake = true;
		}
		else
		{
			m_tStat.fHp -= pOParryBullet->Get_Damage();

			m_bIsHit = true;
			m_dwHitTime = GetTickCount();
			m_eCurState = HIT;
		}
	}


	CDotori* pDotori = dynamic_cast<CDotori*>(_OtherObj);

	if (pDotori)
	{
		m_tStat.fHp -= pDotori->Get_Damage();

		m_bIsHit = true;
		m_dwHitTime = GetTickCount();
		m_eCurState = HIT;
	}

	CFlower* pFlower = dynamic_cast<CFlower*>(_OtherObj);
	if (pFlower)
	{
		m_tStat.fHp -= pFlower->Get_Damage();

		m_bIsHit = true;
		m_dwHitTime = GetTickCount();
		m_eCurState = HIT;
	}

	CJumpEnemy* pJumpE = dynamic_cast<CJumpEnemy*>(_OtherObj);
	if (pJumpE)
	{
		m_tStat.fHp -= pJumpE->Get_Damage();

		m_bIsHit = true;
		m_dwHitTime = GetTickCount();
		m_eCurState = HIT;
	}

	CFlyingMan* pFlying = dynamic_cast<CFlyingMan*>(_OtherObj);
	if (pFlying)
	{
		m_tStat.fHp -= pFlying->Get_Damage();

		m_bIsHit = true;
		m_dwHitTime = GetTickCount();
		m_eCurState = HIT;
	}

	CTaurus* pTau = dynamic_cast<CTaurus*>(_OtherObj);
	if (pTau)
	{
		if (m_bIsParry)
		{
			//m_tStat.fHp -= pTau->Get_Damage();

			//m_bIsHit = true;
			//m_dwHitTime = GetTickCount();
			m_fCurJumpSpeed = m_fInitJumpSpeed;
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CParry_Effect>::Create(m_tInfo.fX, (float)m_HRect.bottom));
			m_bParryShake = true;
			pTau->Kill_Obj();
			//m_eCurState = HIT;
		}
	}

	CSagittarius* pSa = dynamic_cast<CSagittarius*>(_OtherObj);
	if (pSa)
	{
		m_tStat.fHp -= pSa->Get_Damage();

		m_bIsHit = true;
		m_dwHitTime = GetTickCount();
		m_eCurState = HIT;
	}

	CArrow* pArrow = dynamic_cast<CArrow*>(_OtherObj);
	if (pArrow)
	{
		m_tStat.fHp -= pArrow->Get_Damage();

		m_bIsHit = true;
		m_dwHitTime = GetTickCount();
		m_eCurState = HIT;
	}



	if (m_tStat.fHp <= EPSILON)
	{
		m_bDead = true;
	}

	// 프레임 끝나고 false 나오도록




	/*CPlayer* pPlayer = dynamic_cast<CPlayer*>(_OtherObj);
	if (pPlayer)
	{
	m_bDead = true;
	}*/

}

void CPlayer::Key_Input(void)
{//키 누를 때랑 땔 때 스테이트 변경하게 만들기 
	//총쏘기 루틴 참고
	float	fY = 0.f;

	if (m_bIsHit || m_bDead || m_bDash) return;

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		m_HInfo.fX += m_fSpeed;
		m_pFrameKey = L"Player_Right";
		m_eCurState = RUN;
		m_eLookState = LOOK_RIGHT;




		if (CKeyMgr::Get_Instance()->Key_Down('C'))
		{
			if (m_eState == GROUND)
			{
				if (!m_bJump)
				{
					m_fCurJumpSpeed = m_fInitJumpSpeed;
					m_eState = AIR;
					m_eCurState = JUMP;
				}
			}

			else if (m_eState == AIR)
			{
				m_bIsParry = true;

				if (m_bIsParry)
				{
					m_eCurState = PARRY;
				}
			}
		}


		else if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		{
			if (!m_bDash)
			{
				m_bDash = true;
				CObj* pPlayer_Dash = CAbstractFactory<CDash_Effect>::Create(m_tInfo.fX, m_tInfo.fY);
				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, pPlayer_Dash);
				m_dwDashWaitTime = GetTickCount();
			}
		}

		else if (m_dwAttack + 200 < GetTickCount() && CKeyMgr::Get_Instance()->Key_Down('X') && CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		{
			m_eCurState = RUNNING_ATTACK_HOR;
			m_bRun_Shoot = true;
			m_bBulletCnt = true;
		}
	}



	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		if (m_ePreState == CROUCH && m_eCurState == CROUCH)
		{
			Move_Frame(6);
		}
		else
			m_eCurState = CROUCH;

		if (m_eState == GROUND && CKeyMgr::Get_Instance()->Key_Down('C'))
		{
			m_tInfo.fY -= 5.f;
			m_HInfo.fY -= 5.f;
		}
	}


	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		m_HInfo.fX -= m_fSpeed;
		m_pFrameKey = L"Player_Left";
		m_eCurState = RUN;
		m_eLookState = LOOK_LEFT;

		if (CKeyMgr::Get_Instance()->Key_Down('C'))
		{
			if (m_eState == GROUND)
			{
				if (!m_bJump)
				{
					m_fCurJumpSpeed = m_fInitJumpSpeed;
					m_eState = AIR;
					m_eCurState = JUMP;
				}
			}

			else if (m_eState == AIR)
			{
				m_bIsParry = true;

				if (m_bIsParry)
				{
					m_eCurState = PARRY;
				}
			}
		}

		else if (m_dwAttack + 200 < GetTickCount() && GetAsyncKeyState('X') && CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		{
			m_eCurState = RUNNING_ATTACK_HOR;
			m_bRun_Shoot = true;
			m_bBulletCnt = true;
		}

		else if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		{
			if (!m_bDash)
			{
				m_bDash = true;
				CObj* pPlayer_Dash = CAbstractFactory<CDash_Effect>::Create(m_tInfo.fX, m_tInfo.fY);
				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, pPlayer_Dash);
				m_dwDashWaitTime = GetTickCount();
			}
		}
	}

	else if (CKeyMgr::Get_Instance()->Key_Down('C'))
	{

		if (m_eState == GROUND)
		{
			if (!m_bJump)
			{
				m_fCurJumpSpeed = m_fInitJumpSpeed;
				m_eState = AIR;
				m_eCurState = JUMP;
			}
		}

		else if (m_eState == AIR && m_eCurState == JUMP)
		{
			m_bIsParry = true;
			if (m_bIsParry)
			{
				m_eCurState = PARRY;
			}
		}

	}

	else if (m_dwAttack + 300 < GetTickCount() && CKeyMgr::Get_Instance()->Key_Pressing('X'))
	{
		m_bShoot = true;
		m_bBulletCnt = true;
	}

	else if (m_dwAttack + 300 < GetTickCount() && CKeyMgr::Get_Instance()->Key_Pressing('E'))
	{
		m_bDirShoot = true;
		m_bShoot_Dir = true;
	}

	else if (m_dwAttack + 1000 < GetTickCount())
	{
		if (GetAsyncKeyState('M') && GetAsyncKeyState('1'))
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CPotato>::Create());
		}
		m_dwAttack = GetTickCount();
	}

	/*else if (CKeyMgr::Get_Instance()->Key_Down('1'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGEWORLD);
	}

	else if (CKeyMgr::Get_Instance()->Key_Down('2'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGETUTORIAL);
	}*/

	/*else if (CKeyMgr::Get_Instance()->Key_Down('3'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGEROOT);
	}*/

	/*else if (CKeyMgr::Get_Instance()->Key_Down(VK_TAB))
		g_TransparentObj = true;*/


		/*else if (GetAsyncKeyState(VK_SPACE))
		{
			m_bDash = true;
		}*/

	else if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		//CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, Create_Bullet<CGuideBullet>((float)m_tPosin.x, (float)m_tPosin.y));

		//CSoundMgr::Get_Instance()->PlaySound(L"Success.wav", SOUND_EFFECT, g_fSound);
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_F1))
	{
		g_fSound -= 0.1f;

		if (g_fSound < 0.f)
			g_fSound = 0.f;

		CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_EFFECT, g_fSound);
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_F2))
	{
		g_fSound += 0.1f;

		if (g_fSound > 1.f)
			g_fSound = 1.f;

		CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_EFFECT, g_fSound);
	}

	else if (CKeyMgr::Get_Instance()->Key_Down(VK_SHIFT))
	{
		if (m_bDefault_Bullet)
		{
			m_bBounce_Bullet = true;
			m_bDefault_Bullet = false;
		}
		else
		{
			m_bDefault_Bullet = true;
			m_bBounce_Bullet = false;
		}
	}
	else
		//if (m_bShoot == true) return;

		m_eCurState = IDLE;

}


void CPlayer::Parry(void)
{
	if (m_bIsParry)
	{
		if (m_eLookState == LEFT)
		{
			m_eCurState = PARRY;
			m_eLookState = LOOK_LEFT;
		}
		else
		{
			m_eCurState = PARRY;
			m_eLookState = LOOK_RIGHT;
		}
	}
}



void CPlayer::Jumping(void)
{


	//float	fY = 0.f;

	//bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);
	/*
	if (m_bJump)
	{
		m_tInfo.fY -= m_fJumpPower * m_fJumpTime - (9.8f * m_fJumpTime * m_fJumpTime) * 0.5f;
		m_HInfo.fY -= m_fJumpPower * m_fJumpTime - (9.8f * m_fJumpTime * m_fJumpTime) * 0.5f;
		m_fJumpTime += 0.17f;
		m_eState = AIR;

		if (m_eCurState == HIT)
		{
			m_eCurState = HIT;
		}
		else
		{
			m_eCurState = JUMP;
		}

		if (bLineCol && (fY < m_tInfo.fY))
		{
			m_bJump = false;
			m_fJumpTime = 0.f;
			m_tInfo.fY = fY;
			m_HInfo.fY = fY;
			m_eState = GROUND;
		}
	}
	*/
	//if (bLineCol)
	//{
	//	m_tInfo.fY = fY;
	//	m_HInfo.fY = fY;
	//	m_eState = GROUND;

	//}
}

void CPlayer::Offset(void)
{
	//int	iOffsetX = WINCX >> 1;

	int	iOffsetMinX = 400;
	int	iOffsetMaxX = 700;

	int	iOffsetMinY = 400;
	int	iOffsetMaxY = 500;

	int	iScrollX = int(CScrollMgr::Get_Instance()->Get_ScrollX());
	int	iScrollY = int(CScrollMgr::Get_Instance()->Get_ScrollY());

	// 플레이어가 중앙을 기준으로 왼쪽을 향하고 있음
	if (iOffsetMinX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	// 플레이어가 중앙을 기준으로 오른쪽을 향하고 있음
	if (iOffsetMaxX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	if (iOffsetMinY > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	// 플레이어가 중앙을 기준으로 오른쪽을 향하고 있음
	if (iOffsetMaxY < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);

}

void CPlayer::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			if (m_eLookState == LOOK_LEFT)
			{
				m_pFrameKey = L"Player_Left";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 0;
				m_tFrame.dwFrameSpeed = 100;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			else
			{
				m_pFrameKey = L"Player_Right";

				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 0;
				m_tFrame.dwFrameSpeed = 100;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			break;

		case CROUCH:
			if (m_eLookState == LOOK_LEFT)
			{
				m_pFrameKey = L"Player_Left";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 6;
				m_tFrame.iMotion = 8;
				m_tFrame.dwFrameSpeed = 100;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			else
			{
				m_pFrameKey = L"Player_Right";

				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 6;
				m_tFrame.iMotion = 8;
				m_tFrame.dwFrameSpeed = 100;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			break;

		case RUN:
			if (m_eLookState == LOOK_LEFT)
			{
				m_pFrameKey = L"Player_Left";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 15;
				m_tFrame.iMotion = 2;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			else
			{
				m_pFrameKey = L"Player_Right";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 15;
				m_tFrame.iMotion = 2;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			break;

		case DASH:
			if (m_eLookState == LOOK_LEFT)
			{
				m_pFrameKey = L"Player_Dash";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 1;
				m_tFrame.dwFrameSpeed = 40;
				m_tFrame.dwFrameTime = GetTickCount();
			}

			else
			{
				m_pFrameKey = L"Player_Dash";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 0;
				m_tFrame.dwFrameSpeed = 40;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			break;

		case JUMP:
			if (m_eLookState == LOOK_LEFT)
			{
				m_pFrameKey = L"Player_Left";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 1;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			else
			{
				m_pFrameKey = L"Player_Right";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 1;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();

			}
			break;

		case PARRY:
			if (m_eLookState == LOOK_LEFT)
			{
				m_pFrameKey = L"Player_Left";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 6;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
				m_iShakeCnt = 0;
				m_dwShaketimer = GetTickCount();
			}
			else
			{
				m_pFrameKey = L"Player_Right";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 6;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
				m_iShakeCnt = 0;
				m_dwShaketimer = GetTickCount();

			}
			break;

		case ATTACK:
			if (m_eLookState == LOOK_LEFT)
			{
				m_pFrameKey = L"Player_Left";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 2;
				m_tFrame.iMotion = 5;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			else
			{
				m_pFrameKey = L"Player_Right";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 2;
				m_tFrame.iMotion = 5;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			break;

		case ATTACK_UP:
			if (m_eLookState == LOOK_LEFT)
			{
				m_pFrameKey = L"Player_Left";
				m_tFrame.iFrameStart = 16;
				m_tFrame.iFrameEnd = 18;
				m_tFrame.iMotion = 5;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			else
			{
				m_pFrameKey = L"Player_Right";
				m_tFrame.iFrameStart = 16;
				m_tFrame.iFrameEnd = 18;
				m_tFrame.iMotion = 5;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			break;

		case ATTACK_DIR:
			if (m_eLookState == LOOK_LEFT)
			{
				m_pFrameKey = L"Player_Left";
				m_tFrame.iFrameStart = 8;
				m_tFrame.iFrameEnd = 10;
				m_tFrame.iMotion = 5;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			else
			{
				m_pFrameKey = L"Player_Right";
				m_tFrame.iFrameStart = 8;
				m_tFrame.iFrameEnd = 10;
				m_tFrame.iMotion = 5;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			break;


		case RUNNING_ATTACK_HOR:
			if (m_eLookState == LOOK_LEFT)
			{
				m_pFrameKey = L"Player_Left";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 15;
				m_tFrame.iMotion = 3;
				m_tFrame.dwFrameSpeed = 25;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			else
			{
				m_pFrameKey = L"Player_Right";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 15;
				m_tFrame.iMotion = 3;
				m_tFrame.dwFrameSpeed = 25;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			break;


		case RUNNING_ATTACK_DIR:
			if (m_eLookState == LOOK_LEFT)
			{
				m_pFrameKey = L"Player_Left";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 15;
				m_tFrame.iMotion = 4;
				m_tFrame.dwFrameSpeed = 25;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			else
			{
				m_pFrameKey = L"Player_Right";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 15;
				m_tFrame.iMotion = 4;
				m_tFrame.dwFrameSpeed = 25;
				m_tFrame.dwFrameTime = GetTickCount();
			}
			break;

		case HIT:
			if (m_ePreState == JUMP)
			{
				if (m_eLookState == LOOK_LEFT)
				{
					m_pFrameKey = L"Player_Left";
					m_tFrame.iFrameStart = 8;
					m_tFrame.iFrameEnd = 19;
					m_tFrame.iMotion = 1;
					m_tFrame.dwFrameSpeed = 40;
					m_tFrame.dwFrameTime = GetTickCount();
					CObj* pHit_Effect = CAbstractFactory<CHit_Effect>::Create(m_HInfo.fX, (float)m_HRect.top);
					CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, pHit_Effect);
				}
				else
				{
					m_pFrameKey = L"Player_Right";
					m_tFrame.iFrameStart = 8;
					m_tFrame.iFrameEnd = 19;
					m_tFrame.iMotion = 1;
					m_tFrame.dwFrameSpeed = 40;
					m_tFrame.dwFrameTime = GetTickCount();
					CObj* pHit_Effect = CAbstractFactory<CHit_Effect>::Create(m_HInfo.fX, (float)m_HRect.top);
					CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, pHit_Effect);
				}
			}
			else
			{
				if (m_eLookState == LOOK_LEFT)
				{
					m_pFrameKey = L"Player_Left";
					m_tFrame.iFrameStart = 8;
					m_tFrame.iFrameEnd = 19;
					m_tFrame.iMotion = 1;
					m_tFrame.dwFrameSpeed = 40;
					m_tFrame.dwFrameTime = GetTickCount();
				}
				else
				{
					m_pFrameKey = L"Player_Right";
					m_tFrame.iFrameStart = 8;
					m_tFrame.iFrameEnd = 19;
					m_tFrame.iMotion = 1;
					m_tFrame.dwFrameSpeed = 40;
					m_tFrame.dwFrameTime = GetTickCount();
				}
			}
			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.iMotion = 7;
			m_tFrame.dwFrameSpeed = 40;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;

	}
}

void CPlayer::Dash(void)
{

	if (m_dwDashWaitTime + m_fDashCoolTIme * 1000 < GetTickCount())
		m_bDash = false;

	if (m_bDash)
	{
		if (m_eLookState == LEFT)
		{
			m_tInfo.fX -= m_fDashSpeed;
			m_HInfo.fX -= m_fDashSpeed;
			m_eCurState = DASH;
			m_eLookState = LOOK_LEFT;
		}
		else
		{
			m_tInfo.fX += m_fDashSpeed;
			m_HInfo.fX += m_fDashSpeed;
			m_eCurState = DASH;
			m_eLookState = LOOK_RIGHT;
		}
	}
}

void CPlayer::Shoot_Hor(void)
{

	if (m_bShoot)
	{
		if (m_bBulletCnt)
		{
			if (m_eLookState == LOOK_RIGHT)
			{
				if (m_bDefault_Bullet)
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBasicBullet>::Create(m_HInfo.fX + 50, m_HInfo.fY, DIR_RIGHT));
					//CObj* pBullet_Effect = CAbstractFactory<CBullet_Effect>::Create(m_HInfo.fX + 55, m_HInfo.fY, DIR_RIGHT);
					//CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pBullet_Effect);
					m_dwAttack = GetTickCount();
					m_bBulletCnt = false;
				}
				else
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet>::Create(m_HInfo.fX + 50, m_HInfo.fY, DIR_RIGHT));
					CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet_Effect>::Create(m_HInfo.fX + 55, m_HInfo.fY, DIR_RIGHT));
					m_dwAttack = GetTickCount();
					m_bBulletCnt = false;
				}
			}
			else
			{
				if (m_bDefault_Bullet)
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBasicBullet>::Create(m_HInfo.fX - 30, m_HInfo.fY, DIR_LEFT));
					//CObj* pBullet_Effect = CAbstractFactory<CBullet_Effect>::Create(m_HInfo.fX + 55, m_HInfo.fY, DIR_RIGHT);
					//CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pBullet_Effect);
					m_dwAttack = GetTickCount();
					m_bBulletCnt = false;
				}
				else
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet>::Create(m_HInfo.fX - 30, m_HInfo.fY, DIR_LEFT));
					CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet_Effect>::Create(m_HInfo.fX - 55, m_HInfo.fY, DIR_RIGHT));
					m_dwAttack = GetTickCount();
					m_bBulletCnt = false;
				}
			}
		}
		m_eCurState = ATTACK;
		// 프레임 끝나고 false 나오도록
		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			m_eCurState = IDLE;
			m_bShoot = false;
		}
	}
}

void CPlayer::Shoot_DIR(void)
{

	if (m_bDirShoot)
	{
		if (m_bShoot_Dir)
		{
			if (m_eLookState == LOOK_RIGHT)
			{
				if (m_bDefault_Bullet)
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBasicBullet>::Create(m_HInfo.fX + 65, m_HInfo.fY - 65, DIR_RU));
					m_dwAttack = GetTickCount();
					m_bShoot_Dir = false;
				}
				else
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet>::Create(m_HInfo.fX + 65, m_HInfo.fY - 65, DIR_RU));
					CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet_Effect>::Create(m_HInfo.fX + 65, m_HInfo.fY - 65, DIR_RIGHT));
					m_dwAttack = GetTickCount();
					m_bShoot_Dir = false;
				}
			}
			else 
			{
				if (m_bDefault_Bullet && m_eLookState == LOOK_LEFT)
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBasicBullet>::Create(m_HInfo.fX - 65, m_HInfo.fY - 65, DIR_LU));
					m_dwAttack = GetTickCount();
					m_bShoot_Dir = false;
				}
				else
				{
					if (m_bBounce_Bullet && m_eLookState == LOOK_LEFT)
					{
						CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet>::Create(m_HInfo.fX - 65, m_HInfo.fY - 65, DIR_LU));
						CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet_Effect>::Create(m_HInfo.fX - 55, m_HInfo.fY - 65, DIR_RIGHT));
						m_dwAttack = GetTickCount();
						m_bShoot_Dir = false;
					}
				}
			}
		}
	

		m_eCurState = ATTACK_DIR;
		// 프레임 끝나고 false 나오도록
		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			m_eCurState = IDLE;
			m_bDirShoot = false;
		}
	}
}


void CPlayer::Run_Shoot_Hor(void)
{

	if (m_bRun_Shoot)
	{
		if (m_bBulletCnt)
		{
			if (m_eLookState == LOOK_RIGHT)
			{
				if (m_bDefault_Bullet)
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBasicBullet>::Create(m_HInfo.fX + 80, m_HInfo.fY + 15, DIR_RIGHT));
					m_dwAttack = GetTickCount();
					m_bBulletCnt = false;
				}
				else
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet>::Create(m_HInfo.fX + 80, m_HInfo.fY + 15, DIR_RIGHT));
					CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet_Effect>::Create(m_HInfo.fX + 80, m_HInfo.fY + 15, DIR_RIGHT));
					m_dwAttack = GetTickCount();
					m_bBulletCnt = false;
				}
			}
			else
			{
				if (m_bDefault_Bullet)
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBasicBullet>::Create(m_HInfo.fX - 80, m_HInfo.fY + 15, DIR_LEFT));
					m_dwAttack = GetTickCount();
					m_bBulletCnt = false;
				}
				else
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet>::Create(m_HInfo.fX - 80, m_HInfo.fY + 15, DIR_LEFT));
					CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet_Effect>::Create(m_HInfo.fX - 80, m_HInfo.fY + 15, DIR_RIGHT));
					m_dwAttack = GetTickCount();
					m_bBulletCnt = false;
				}
			}
		}
		// m_pFrameKey = L"Run_Shoot";
		m_eCurState = RUNNING_ATTACK_HOR;
		// 프레임 끝나고 false 나오도록
		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			m_eCurState = IDLE;
			m_bRun_Shoot = false;
		}
	}
}



template<typename T>
CObj* CPlayer::Create_Bullet(float _fX, float _fY, DIR eDir)
{
	CObj*	pBullet = CAbstractFactory<T>::Create(_fX, _fY, m_fAngle);

	pBullet->Set_Dir(eDir);

	return pBullet;
}

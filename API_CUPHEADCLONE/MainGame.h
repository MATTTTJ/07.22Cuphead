#pragma once

//#include "Include.h"
#include "Include.h"

#include "Player.h"
#include "Bullet.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(void);
	void		Release(void);

private:
	HDC				m_hDC;
	
	DWORD			m_dwTime;
	int				m_iFPS;
	TCHAR			m_szFPS[32];	
};

// 디자인 패턴 : 코드의 구조들을 일정한 형태로 만들어 재사용하기 편리하게 만든 일정한 패턴
// 클래스 간의 관계, 클래스 간의 행동양식을 공통적인 요소별로 분류하고 객체 지향적인 설계의 노하우를 정리해 놓은 학문

// 추상 팩토리 패턴 : 생성 패턴의 한 방법으로 인스턴스를 만드는 절차를 추상화시킨 패턴

// 반복자 패턴(이터레이터 패턴) : 내부 표현 방식은 공개하지 않고 순차적인 접근 방법을 제공하는 패턴

// 중재자 패턴(메디에이터 패턴) : 상호작용하는 객체들이 서고 복잡한 관계를 맺고 있을 경우 별도의 형식으로 정의하여 중재하는 객체를 두는 패턴

// 싱글톤 패턴 : 단 하나의 인스턴스(객체)만 생성하여 사용하는 패턴
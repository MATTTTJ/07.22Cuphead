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

// ������ ���� : �ڵ��� �������� ������ ���·� ����� �����ϱ� ���ϰ� ���� ������ ����
// Ŭ���� ���� ����, Ŭ���� ���� �ൿ����� �������� ��Һ��� �з��ϰ� ��ü �������� ������ ���Ͽ츦 ������ ���� �й�

// �߻� ���丮 ���� : ���� ������ �� ������� �ν��Ͻ��� ����� ������ �߻�ȭ��Ų ����

// �ݺ��� ����(���ͷ����� ����) : ���� ǥ�� ����� �������� �ʰ� �������� ���� ����� �����ϴ� ����

// ������ ����(�޵����� ����) : ��ȣ�ۿ��ϴ� ��ü���� ���� ������ ���踦 �ΰ� ���� ��� ������ �������� �����Ͽ� �����ϴ� ��ü�� �δ� ����

// �̱��� ���� : �� �ϳ��� �ν��Ͻ�(��ü)�� �����Ͽ� ����ϴ� ����
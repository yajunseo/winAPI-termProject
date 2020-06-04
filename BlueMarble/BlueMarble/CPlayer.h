#pragma once
#include "windows.h"

class CPlayer
{
	HDC		m_PlayerImgDC;
	HBITMAP charBit[2];
	int bitIndex;
	int characterNum;
	int m_PlayerImgWidth;
	int m_PlayerImgHeight;

	int xPos, yPos;

	int money;

public:
	CPlayer();
	~CPlayer();

	void Init_Player(HWND a_hWnd, HINSTANCE hInst, int n);
	void Update_Player(float a_DeltaTime, RECT& a_RT);
	void Render_Player(HDC a_hDC);
	void Destroy_Player();

};

extern CPlayer g_Player;
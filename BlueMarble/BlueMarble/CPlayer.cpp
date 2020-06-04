#include "framework.h"
#include "CPlayer.h"
#include "Resource.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init_Player(HWND a_hWnd, HINSTANCE hInst, int n)
{
	characterNum = n;
	xPos = 50;
	yPos = 50;
	if (characterNum == 1)
	{
		charBit[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
		charBit[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
	}

	else if (characterNum == 2)
	{
		charBit[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP4));
		charBit[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP5));
	}

	HDC hdc = GetDC(a_hWnd);
	m_PlayerImgDC = CreateCompatibleDC(hdc);
	SelectObject(m_PlayerImgDC, charBit[0]);
	ReleaseDC(a_hWnd, hdc);

	BITMAP bm;
	GetObject(charBit[0], sizeof(BITMAP), &bm);
	m_PlayerImgWidth = bm.bmWidth;
	m_PlayerImgHeight = bm.bmHeight;
}

void CPlayer::Update_Player(float a_DeltaTime, RECT& a_RT)
{

}

void CPlayer::Render_Player(HDC a_hDC)
{
	//////StretchBlt(a_hDC, xPos, yPos,50, 50,
	//////	  m_PlayerImgDC,xPos, yPos,  m_PlayerImgWidth, m_PlayerImgHeight, SRCCOPY);

	//StretchBlt(a_hDC, 0, 0, 50, 50, m_PlayerImgDC, 0, 0, m_PlayerImgWidth, m_PlayerImgHeight, SRCCOPY);
	TransparentBlt(a_hDC, 0, 0, 50, 50, m_PlayerImgDC, 0, 0, m_PlayerImgWidth, m_PlayerImgHeight, RGB(0, 0, 0));
}

void CPlayer::Destroy_Player()
{
	if (m_PlayerImgDC != NULL)
	{
		DeleteDC(m_PlayerImgDC);
		m_PlayerImgDC = NULL;
	}

	if (charBit[0] != NULL)
	{
		DeleteObject(charBit[0]);
		charBit[0] = NULL;
	}

	if (charBit[1] != NULL)
	{
		DeleteObject(charBit[1]);
		charBit[1] = NULL;
	}
}

CPlayer g_Player;
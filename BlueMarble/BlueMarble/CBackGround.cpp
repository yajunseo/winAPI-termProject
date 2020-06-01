#include "framework.h"
#include "CBackGround.h"
#include "Resource.h"

CBackGround::CBackGround()
{
	m_SocketImg = NULL;
}

CBackGround::~CBackGround()
{
}

void CBackGround::BG_Init(HWND a_hWnd, HINSTANCE hInst)
{
	HDC hdc = GetDC(a_hWnd);
	m_BGImgDC = CreateCompatibleDC(hdc);
	//m_hTexImgBMP = (HBITMAP)LoadImage(NULL, _T(".\\Image\\BG1.bmp"),
		//IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_hTexImgBMP = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));

	SelectObject(m_BGImgDC, m_hTexImgBMP);
	ReleaseDC(a_hWnd, hdc);

	BITMAP bm;
	GetObject(m_hTexImgBMP, sizeof(BITMAP), &bm);
	m_TexImgWidth = bm.bmWidth;
	m_TexImgHeight = bm.bmHeight;

}

void CBackGround::BG_Update()
{
}

void CBackGround::BG_Render(HDC a_hdc, RECT& a_RT)
{
	StretchBlt(a_hdc, 0, 0, a_RT.right, a_RT.bottom, m_BGImgDC, 0, 0, m_TexImgWidth, m_TexImgHeight, SRCCOPY);
}

void CBackGround::BG_Destroy()
{
	if (m_BGImgDC != NULL)
	{
		DeleteDC(m_BGImgDC);
		m_BGImgDC = NULL;
	}

	if (m_hTexImgBMP != NULL)
	{
		DeleteObject(m_hTexImgBMP);
		m_hTexImgBMP = NULL;
	}
}


CBackGround g_BGround;
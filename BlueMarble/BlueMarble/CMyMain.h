#pragma once

class CMyMain
{
	HWND m_hWnd = NULL;
	RECT m_Rect;

	ULONG_PTR m_gdiplusToken = NULL;

	HDC m_hBackDC = NULL;
	HBITMAP m_hBackBitmap = NULL;


public:
	CMyMain();
	~CMyMain();
	
	void MainInit(HWND hWnd, HINSTANCE hInst);
	void MainUpdate(HWND hWnd);
	void MainRender(HWND hWnd);
	void MainDestroy();
};

extern CMyMain g_CMyMain;


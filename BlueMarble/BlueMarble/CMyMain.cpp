#include "framework.h"
#include "CMyMain.h"
#include "CBackGround.h"

#include <ole2.h>  
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;


CMyMain::CMyMain()
{
}

CMyMain::~CMyMain()
{
}

void CMyMain::MainInit(HWND hWnd, HINSTANCE hInst)
{
	m_hWnd = hWnd;
	GetClientRect(hWnd, &m_Rect);

	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	HDC hdc = GetDC(hWnd);
	m_hBackDC = CreateCompatibleDC(hdc);
	m_hBackBitmap = CreateCompatibleBitmap(hdc, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	SelectObject(m_hBackDC, m_hBackBitmap);
	ReleaseDC(hWnd, hdc);

	g_BGround.BG_Init(hWnd, hInst);
}

void CMyMain::MainUpdate(HWND hWnd)
{
	if (m_hBackDC == NULL)
		return;

	GetClientRect(hWnd, &m_Rect);

	//g_BGround.BG_Update();

}

void CMyMain::MainRender(HWND hWnd)
{
	if (m_hBackDC == NULL)
		return;

	g_BGround.BG_Render(m_hBackDC, m_Rect);

	static HDC hdc;
	hdc = GetDC(hWnd);
	BitBlt(hdc, 0, 0, m_Rect.right, m_Rect.bottom, m_hBackDC, 0, 0, SRCCOPY);
	ReleaseDC(hWnd, hdc);
}

void CMyMain::MainDestroy()
{
	g_BGround.BG_Destroy();

	if (m_hBackBitmap != NULL)
	{
		DeleteObject(m_hBackBitmap);
		m_hBackBitmap = NULL;
	}

	if (m_hBackDC != NULL)
	{
		DeleteDC(m_hBackDC);
		m_hBackDC = NULL;
	}

	if (m_gdiplusToken != NULL)
	{
		GdiplusShutdown(m_gdiplusToken);
		m_gdiplusToken = NULL;
	}
}

CMyMain g_CMyMain;
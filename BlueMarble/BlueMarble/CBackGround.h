#pragma 
#include <ole2.h>      
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;


class CBackGround
{
	HDC m_BGImgDC;
	HBITMAP m_hTexImgBMP;
	Image* m_SocketImg;
	int m_TexImgWidth;
	int m_TexImgHeight;
public:
	CBackGround();
	~CBackGround();

	void BG_Init(HWND a_hWnd, HINSTANCE hInst);
	void BG_Update();
	void BG_Render(HDC a_hdc, RECT& a_RT);
	void BG_Destroy();

};

extern CBackGround g_BGround;
// BlueMarble.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "BlueMarble.h"
#include "Resource.h"
#include "CPlayer.h"
#include "CBuild.h"
#include <mmsystem.h>

#pragma comment(lib, "Msimg32.lib")

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
int ScreenWidth = 1024;
int ScreenHeight = 1024;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_BLUEMARBLE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BLUEMARBLE));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BLUEMARBLE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BLUEMARBLE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW| WS_CLIPCHILDREN,
      0,0, ScreenWidth, ScreenHeight, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
CPlayer player1, player2;
int boardArr1[40][2];
int boardArr2[40][2];
#define IDC_BUTTON1 200
#define IDC_BUTTON2 201
#define IDC_EDIT1 202
#define IDC_EDIT2 203

#define IDC_CHECK1 204
#define IDC_CHECK2 205
#define IDC_CHECK3 206
#define IDC_CHECK4 207
#define IDC_CHECK5 208
#define IDC_CHECK6 209
#define IDC_CHECK7 212
#define IDC_CHECK8 213

#define IDC_BUTTON3 210
#define IDC_BUTTON4 211
#define IDC_EDIT3 214
#define IDC_EDIT4 215
#define IDC_EDIT5 216
#define IDC_EDIT6 217

#define IDC_BUTTON5 218
#define IDC_EDIT7 219
int turn = 1;
int boardOwn[40][4];
bool dropDice = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    srand((DWORD)GetTickCount());
    HDC hdc, mem1dc, mem2dc;
    static HBITMAP hbit1, hBack, hChar[4], oldBit1, oldBit2, hBuild[6], hDiceBit[6];
    static RECT rc;
    BITMAP bm;
    static int bitIndex = 0;
    static HWND hDice, hTurn, hMoney[2], hCheck[8], hBuy, hPrice[4], hBuyOther, hCurrentTurn;
    float boardWidth;
    float boardHeight;
    TCHAR str[100];
    static int dice, dice2;
    int temp;
    CBuild build;
    int turnMoney = 300;
    static bool buyChance = false;
    switch (message)
    {
    case WM_CREATE:
        GetClientRect(hWnd, &rc);
        PlaySound(_T("Sound"), NULL, SND_ASYNC | SND_LOOP);
        SetTimer(hWnd, 1, 150, NULL);
        hBack = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
        hChar[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
        hChar[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
        hChar[2] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP4));
        hChar[3] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP5));
        hBuild[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP6));
        hBuild[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP7));
        hBuild[2] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP9));
        hBuild[3] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP11));
        hBuild[4] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP8));
        hBuild[5] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP10));
        hDiceBit[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP12));
        hDiceBit[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP13));
        hDiceBit[2] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP14));
        hDiceBit[3] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP15));
        hDiceBit[4] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP16));
        hDiceBit[5] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP17));

        boardWidth = (rc.right - rc.left - 200) / 10;
        boardHeight = (rc.bottom - rc.top - 200) / 10;

        for (int i = 0; i < 10; i++)
        {
            boardArr1[i][0] =rc.right - 150 - boardWidth*(i);
            boardArr1[i][1] = rc.bottom - 100;
            boardArr2[i][0] = rc.right - 110 - boardWidth * (i);
            boardArr2[i][1] = rc.bottom - 100;
        }
        for (int i = 10; i < 20; i++)
        {
            boardArr1[i][0] = rc.left + 30;
            boardArr1[i][1] = rc.bottom - 155 - boardHeight * (i-10);
            boardArr2[i][0] = rc.left + 30;
            boardArr2[i][1] = rc.bottom - 125 - boardHeight * (i - 10);
        }
        for (int i = 20; i < 30; i++)
        {
            boardArr1[i][0] = rc.left + 95 + boardWidth * (i-20);
            boardArr1[i][1] = rc.top + 20;
            boardArr2[i][0] = rc.left + 55 + boardWidth * (i-20);
            boardArr2[i][1] = rc.top + 20;
        }
        for (int i = 30; i < 40; i++)
        {
            boardArr1[i][0] = rc.right - 90;
            boardArr1[i][1] = rc.top + 55 + boardHeight * (i - 30);
            boardArr2[i][0] = rc.right - 90;
            boardArr2[i][1] = rc.top + 85 + boardHeight * (i - 30);
        }
        hDice = CreateWindow(_T("button"), _T("주사위 굴리기"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON
            , rc.right / 2 - 200, rc.top + 300, 120, 50, hWnd, (HMENU)IDC_BUTTON1, hInst, NULL);
        hBuy = CreateWindow(_T("button"), _T("구입하기"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON
            , rc.right / 2 - 60, rc.top + 300, 120, 50, hWnd, (HMENU)IDC_BUTTON3, hInst, NULL);
        hTurn = CreateWindow(_T("button"), _T("턴 종료"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON 
            , rc.right / 2 + 80, rc.top + 300, 120, 50, hWnd, (HMENU)IDC_BUTTON2, hInst, NULL);
        hMoney[0] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_RIGHT 
            , rc.left + 250, rc.bottom - 360, 200, 25, hWnd, (HMENU)IDC_EDIT1, hInst, NULL);
        hMoney[1] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_RIGHT 
            , rc.right - 420, rc.bottom - 360, 200, 25, hWnd, (HMENU)IDC_EDIT2, hInst, NULL);
        hCheck[0] = CreateWindow(_T("button"), _T("땅 "), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX 
            , rc.left + 215, rc.bottom - 300, 60, 25, hWnd, (HMENU)IDC_CHECK1, hInst, NULL);
        hCheck[1] = CreateWindow(_T("button"), _T("별장"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX 
            , rc.left + 275, rc.bottom - 300, 60, 25, hWnd, (HMENU)IDC_CHECK2, hInst, NULL);
        hCheck[2] = CreateWindow(_T("button"), _T("빌딩"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX 
            , rc.left + 335, rc.bottom - 300, 60, 25, hWnd, (HMENU)IDC_CHECK3, hInst, NULL);
        hCheck[3] = CreateWindow(_T("button"), _T("호텔"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX 
            , rc.left + 395, rc.bottom - 300, 60, 25, hWnd, (HMENU)IDC_CHECK4, hInst, NULL);
        hCheck[4] = CreateWindow(_T("button"), _T("땅 "), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX 
            , rc.left + 555, rc.bottom - 300, 60, 25, hWnd, (HMENU)IDC_CHECK5, hInst, NULL);
        hCheck[5] = CreateWindow(_T("button"), _T("별장"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX 
            , rc.left + 615, rc.bottom - 300, 60, 25, hWnd, (HMENU)IDC_CHECK6, hInst, NULL);
        hCheck[6] = CreateWindow(_T("button"), _T("빌딩"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX 
            , rc.left + 675, rc.bottom - 300, 60, 25, hWnd, (HMENU)IDC_CHECK7, hInst, NULL);
        hCheck[7] = CreateWindow(_T("button"), _T("호텔"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX 
            , rc.left + 735, rc.bottom - 300, 60, 25, hWnd, (HMENU)IDC_CHECK8, hInst, NULL);
        hPrice[0] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_RIGHT 
            , rc.left + 200, rc.top + 360, 150, 25, hWnd, (HMENU)IDC_EDIT3, hInst, NULL);
        hPrice[1] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_RIGHT 
            , rc.left + 350, rc.top + 360, 150, 25, hWnd, (HMENU)IDC_EDIT4, hInst, NULL);
        hPrice[2] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_RIGHT 
            , rc.left + 500, rc.top + 360, 150, 25, hWnd, (HMENU)IDC_EDIT5, hInst, NULL);
        hPrice[3] = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_RIGHT 
            , rc.left + 650, rc.top + 360, 150, 25, hWnd, (HMENU)IDC_EDIT6, hInst, NULL);
        hCurrentTurn = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_RIGHT
            , rc.right/2- 50, rc.top + 400, 100, 25, hWnd, (HMENU)IDC_EDIT7, hInst, NULL);
        hBuy = CreateWindow(_T("button"), _T("인수하기(+500)"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON
            , rc.right / 2 - 60, rc.bottom - 250, 120, 50, hWnd, (HMENU)IDC_BUTTON5, hInst, NULL);
        InvalidateRect(hWnd, NULL, true);
        break;
    case WM_TIMER:

        switch (wParam)
        {
        case 1:
            build.setRC(rc.left, rc.top, rc.right, rc.bottom);
            hdc = GetDC(hWnd);
            if (hbit1 == NULL)
                hbit1 = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);

            mem1dc = CreateCompatibleDC(hdc);
            mem2dc = CreateCompatibleDC(mem1dc);

            oldBit1 = (HBITMAP)SelectObject(mem1dc, hbit1);
            oldBit2 = (HBITMAP)SelectObject(mem2dc, hBack);

            GetObject(hBack, sizeof(BITMAP), &bm);
            StretchBlt(mem1dc, rc.left, rc.top, rc.right, rc.bottom, mem2dc, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

            oldBit2 = (HBITMAP)SelectObject(mem2dc, hChar[bitIndex]);
            GetObject(hChar[bitIndex], sizeof(BITMAP), &bm);
            TransparentBlt(mem1dc, boardArr1[player1.getPosition()][0], boardArr1[player1.getPosition()][1], 60, 60, mem2dc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0, 0, 0));

            oldBit2 = (HBITMAP)SelectObject(mem2dc, hChar[bitIndex + 2]);
            GetObject(hChar[bitIndex], sizeof(BITMAP), &bm);
            TransparentBlt(mem1dc, boardArr2[player2.getPosition()][0], boardArr2[player2.getPosition()][1], 60, 60, mem2dc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0, 0, 0));

            for (int i = 0; i < 40; i++)
            {
                if(boardOwn[i][0] == 1)
                {
                    if (boardOwn[i][1] == 1)
                    {
                        oldBit2 = (HBITMAP)SelectObject(mem2dc, hBuild[0]);
                        GetObject(hBuild[0], sizeof(BITMAP), &bm);
                        TransparentBlt(mem1dc, build.getVillaX(i), build.getVillaY(i), 20, 20, mem2dc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0, 0, 255));
                    }

                    if (boardOwn[i][2] == 1)
                    {
                        oldBit2 = (HBITMAP)SelectObject(mem2dc, hBuild[1]);
                        GetObject(hBuild[1], sizeof(BITMAP), &bm);
                        TransparentBlt(mem1dc, build.getBuildingX(i), build.getBuildingY(i), 25, 25, mem2dc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0, 0, 255));
                    }

                    if (boardOwn[i][3] == 1)
                    {
                        oldBit2 = (HBITMAP)SelectObject(mem2dc, hBuild[2]);
                        GetObject(hBuild[2], sizeof(BITMAP), &bm);
                        TransparentBlt(mem1dc, build.getHotelX(i), build.getHotelY(i), 25, 25, mem2dc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0, 0, 255));
                    }
                }
                else if (boardOwn[i][0] == 2)
                {
                    if (boardOwn[i][1] == 1)
                    {
                        oldBit2 = (HBITMAP)SelectObject(mem2dc, hBuild[3]);
                        GetObject(hBuild[3], sizeof(BITMAP), &bm);
                        TransparentBlt(mem1dc, build.getVillaX(i), build.getVillaY(i), 20, 20, mem2dc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0, 0, 255));
                    }

                    if (boardOwn[i][2] == 1)
                    {
                        oldBit2 = (HBITMAP)SelectObject(mem2dc, hBuild[4]);
                        GetObject(hBuild[4], sizeof(BITMAP), &bm);
                        TransparentBlt(mem1dc, build.getBuildingX(i), build.getBuildingY(i), 25, 25, mem2dc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0, 0, 255));
                    }

                    if (boardOwn[i][3] == 1)
                    {
                        oldBit2 = (HBITMAP)SelectObject(mem2dc, hBuild[5]);
                        GetObject(hBuild[5], sizeof(BITMAP), &bm);
                        TransparentBlt(mem1dc, build.getHotelX(i), build.getHotelY(i), 25, 25, mem2dc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0, 0, 255));
                    }
                }
            }
            for(int i=1;i<=6;i++)
            {
                if (dice == i)
                {
                    oldBit2 = (HBITMAP)SelectObject(mem2dc, hDiceBit[i - 1]);
                    GetObject(hDiceBit[i - 1], sizeof(BITMAP), &bm);
                    TransparentBlt(mem1dc, rc.left + 400, rc.top + 200, 75, 75, mem2dc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0, 0, 255));
                }

                if (dice2 == i)
                {
                    oldBit2 = (HBITMAP)SelectObject(mem2dc, hDiceBit[i - 1]);
                    GetObject(hDiceBit[i - 1], sizeof(BITMAP), &bm);
                    TransparentBlt(mem1dc, rc.left + 530, rc.top + 200, 75, 75, mem2dc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0, 0, 255));
                }
            }



            SelectObject(mem1dc, oldBit1);
            SelectObject(mem2dc, oldBit2);
            
            DeleteDC(mem2dc);
            DeleteDC(mem1dc);
            ReleaseDC(hWnd, hdc);

            bitIndex++;
            bitIndex %= 2;
            break;
        
        default:
            break;
        }
        InvalidateRect(hWnd, NULL, false);

        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDC_BUTTON1:
                dice = rand() % 6 + 1;
                dice2 = rand() % 6 + 1;
                if (turn == 1 && !dropDice)
                {
                    temp = player1.getPosition();
                    temp += (dice + dice2);
                    if (temp > 39)
                    {
                        player1.setMoney(player1.getMoney() + turnMoney);
                        temp %= 40;
                    }
                    player1.setPosition(temp);
                    dropDice = true;
                    
                    wsprintf(str, _T("땅  : %d 원"), build.getPrice(player1.getPosition(), 0));
                    SetDlgItemText(hWnd, IDC_EDIT3, str);
                    wsprintf(str, _T("별장: %d 원"), build.getPrice(player1.getPosition(), 1));
                    SetDlgItemText(hWnd, IDC_EDIT4, str);
                    wsprintf(str, _T("빌딩: %d 원"), build.getPrice(player1.getPosition(), 2));
                    SetDlgItemText(hWnd, IDC_EDIT5, str);
                    wsprintf(str, _T("호텔: %d 원"), build.getPrice(player1.getPosition(), 3));
                    SetDlgItemText(hWnd, IDC_EDIT6, str);

                    if (boardOwn[player1.getPosition()][0] == 2)
                    {
                        buyChance = true;

                        temp = 0;
                        if (boardOwn[player1.getPosition()][1] == 1)
                            temp += build.getPrice(player1.getPosition(), 1);

                        if (boardOwn[player1.getPosition()][2] == 1)
                            temp += build.getPrice(player1.getPosition(), 2);

                        if (boardOwn[player1.getPosition()][3] == 1)
                            temp += build.getPrice(player1.getPosition(), 3);

                        player1.setMoney(player1.getMoney() - temp);

                        if (player1.getMoney() < 0)
                        {
                            MessageBox(hWnd, _T("플레이어2 승리"), _T("게임 종료"), MB_OK);
                            DestroyWindow(hWnd);
                        }
                    }
                }
                else if (turn == 2 && !dropDice)
                {
                    temp = player1.getPosition();
                    temp += (dice + dice2);
                    if (temp > 39)
                    {
                        player2.setMoney(player2.getMoney() + turnMoney);
                        temp %= 40;
                    }
                    player2.setPosition(temp);
                    dropDice = true;

                    wsprintf(str, _T("땅  : %d 원"), build.getPrice(player1.getPosition(), 0));
                    SetDlgItemText(hWnd, IDC_EDIT3, str);
                    wsprintf(str, _T("별장: %d 원"), build.getPrice(player1.getPosition(), 1));
                    SetDlgItemText(hWnd, IDC_EDIT4, str);
                    wsprintf(str, _T("빌딩: %d 원"), build.getPrice(player1.getPosition(), 2));
                    SetDlgItemText(hWnd, IDC_EDIT5, str);
                    wsprintf(str, _T("호텔: %d 원"), build.getPrice(player1.getPosition(), 3));
                    SetDlgItemText(hWnd, IDC_EDIT6, str);

                    if (boardOwn[player2.getPosition()][0] == 1)
                    {
                        buyChance = true;

                        temp = 0;
                        if (boardOwn[player2.getPosition()][1] == 1)
                            temp += build.getPrice(player2.getPosition(), 1);

                        if (boardOwn[player2.getPosition()][2] == 1)
                            temp += build.getPrice(player2.getPosition(), 2);

                        if (boardOwn[player2.getPosition()][3] == 1)
                            temp += build.getPrice(player2.getPosition(), 3);

                        player2.setMoney(player2.getMoney() - temp);

                        if (player2.getMoney() < 0)
                        {
                            MessageBox(hWnd, _T("플레이어1 승리"), _T("게임 종료"), MB_OK);
                        }
                    }
                }
                break;
            case IDC_BUTTON2:
                CheckDlgButton(hWnd, IDC_CHECK1, BST_UNCHECKED);
                CheckDlgButton(hWnd, IDC_CHECK2, BST_UNCHECKED);
                CheckDlgButton(hWnd, IDC_CHECK3, BST_UNCHECKED);
                CheckDlgButton(hWnd, IDC_CHECK4, BST_UNCHECKED);
                CheckDlgButton(hWnd, IDC_CHECK5, BST_UNCHECKED);
                CheckDlgButton(hWnd, IDC_CHECK6, BST_UNCHECKED);
                CheckDlgButton(hWnd, IDC_CHECK7, BST_UNCHECKED);
                CheckDlgButton(hWnd, IDC_CHECK8, BST_UNCHECKED);
                buyChance = false;
                if (turn == 1)
                    turn = 2;
                else
                    turn = 1;
                dropDice = false;
                break;
            case IDC_BUTTON3:
                temp = player1.getPosition();
                if (turn == 1)
                {
                    if (temp == 2 || temp == 7 || temp == 12 || temp == 17 || temp == 22 || temp == 35)
                    {
                        player1.setMoney(player1.getMoney() + 1000);
                    }
                    else if (temp == 20 || temp == 38)
                    {
                        player1.setMoney(player1.getMoney() - 2000);
                        if (player1.getMoney() < 0)
                        {
                            MessageBox(hWnd, _T("플레이어2 승리"), _T("게임 종료"), MB_OK);
                            DestroyWindow(hWnd);
                        }
                    }
                    if (temp != 0 && temp != 2 && temp != 7 && temp != 10 && temp != 12 && temp != 17 && temp != 20 && temp != 22 && temp != 30 && temp != 35 && temp != 38)
                    {
                        temp = 0;
                        if (boardOwn[player1.getPosition()][0] != 2)
                        {
                            if (SendMessage(hCheck[0], BM_GETCHECK, 0, 0) == BST_CHECKED && boardOwn[player1.getPosition()][0] == 0)
                            {
                                temp += build.getPrice(player1.getPosition(), 0);
                                boardOwn[player1.getPosition()][0] = 1;
                            }
                            if (SendMessage(hCheck[1], BM_GETCHECK, 0, 0) == BST_CHECKED && boardOwn[player1.getPosition()][1] == 0)
                            {
                                temp += build.getPrice(player1.getPosition(), 1);
                                boardOwn[player1.getPosition()][1] = 1;
                            }
                            if (SendMessage(hCheck[2], BM_GETCHECK, 0, 0) == BST_CHECKED && boardOwn[player1.getPosition()][2] == 0)
                            {
                                temp += build.getPrice(player1.getPosition(), 2);
                                boardOwn[player1.getPosition()][2] = 1;
                            }
                            if (SendMessage(hCheck[3], BM_GETCHECK, 0, 0) == BST_CHECKED && boardOwn[player1.getPosition()][3] == 0)
                            {
                                temp += build.getPrice(player1.getPosition(), 3);
                                boardOwn[player1.getPosition()][3] = 1;
                            }
                            player1.setMoney(player1.getMoney() - temp);
                        }
                    }
                }
                else if (turn == 2)
                {
                    temp = player2.getPosition();
                    if (temp == 2 || temp == 7 || temp == 12 || temp == 17 || temp == 22 || temp == 35)
                    {
                        player2.setMoney(player2.getMoney() + 1000);
                    }
                    else if (temp == 20 || temp == 38)
                    {
                        player2.setMoney(player2.getMoney() - 2000);
                        if (player2.getMoney() < 0)
                        {
                            MessageBox(hWnd, _T("플레이어1 승리"), _T("게임 종료"), MB_OK);
                            DestroyWindow(hWnd);
                        }
                    }
                    if (temp != 0 && temp != 2 && temp != 7 && temp != 10 && temp != 12 && temp != 17 && temp != 20 && temp != 22 && temp != 30 && temp != 35 && temp != 38)
                    {
                        if (boardOwn[player2.getPosition()][0] != 1)
                        {
                            temp = 0;
                            if (SendMessage(hCheck[4], BM_GETCHECK, 0, 0) == BST_CHECKED && boardOwn[player2.getPosition()][0] == 0)
                            {
                                temp += build.getPrice(player2.getPosition(), 0);
                                boardOwn[player2.getPosition()][0] = 2;
                            }
                            if (SendMessage(hCheck[5], BM_GETCHECK, 0, 0) == BST_CHECKED && boardOwn[player2.getPosition()][1] == 0)
                            {
                                temp += build.getPrice(player2.getPosition(), 1);
                                boardOwn[player2.getPosition()][1] = 1;
                            }
                            if (SendMessage(hCheck[6], BM_GETCHECK, 0, 0) == BST_CHECKED && boardOwn[player2.getPosition()][2] == 0)
                            {
                                temp += build.getPrice(player2.getPosition(), 2);
                                boardOwn[player2.getPosition()][2] = 1;
                            }
                            if (SendMessage(hCheck[7], BM_GETCHECK, 0, 0) == BST_CHECKED && boardOwn[player2.getPosition()][3] == 0)
                            {
                                temp += build.getPrice(player2.getPosition(), 3);
                                boardOwn[player2.getPosition()][3] = 1;
                            }
                            player2.setMoney(player2.getMoney() - temp);
                        }
                    }
                }
                temp = 0;
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDC_BUTTON5:
                if (buyChance)
                {
                    if (turn == 1)
                    {
                        temp = 0;
                        if (boardOwn[player1.getPosition()][1] == 1)
                            temp += build.getPrice(player1.getPosition(), 1);

                        if (boardOwn[player1.getPosition()][2] == 1)
                            temp += build.getPrice(player1.getPosition(), 2);

                        if (boardOwn[player1.getPosition()][3] == 1)
                            temp += build.getPrice(player1.getPosition(), 3);

                        if (player1.getMoney() <= (temp+500))
                        {
                            MessageBox(hWnd, _T("돈이 부족합니다"), _T("불가"), MB_OK);
                            break;
                        }
                        player1.setMoney(player1.getMoney() - temp + 500);
                        player2.setMoney(player2.getMoney() + temp + 500);
                        boardOwn[player1.getPosition()][0] = 1;

                    }
                    else if (turn == 2)
                    {
                        temp = 0;
                        if (boardOwn[player2.getPosition()][1] == 1)
                            temp += build.getPrice(player2.getPosition(), 1);

                        if (boardOwn[player2.getPosition()][2] == 1)
                            temp += build.getPrice(player2.getPosition(), 2);

                        if (boardOwn[player2.getPosition()][3] == 1)
                            temp += build.getPrice(player2.getPosition(), 3);

                        if (player2.getMoney() <= (temp + 500))
                        {
                            MessageBox(hWnd, _T("돈이 부족합니다"), _T("불가"), MB_OK);
                            break;
                        }
                        player2.setMoney(player2.getMoney() - temp + 500);
                        player1.setMoney(player1.getMoney() + temp + 500);
                        boardOwn[player2.getPosition()][0] = 2;

                    }
                }
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            mem1dc = CreateCompatibleDC(hdc);

            oldBit1 = (HBITMAP)SelectObject(mem1dc, hbit1);
            BitBlt(hdc, rc.left, rc.top, rc.right, rc.bottom, mem1dc, 0, 0, SRCCOPY);

            wsprintf(str, _T("%d 원"), player1.getMoney());
            SetDlgItemText(hWnd, IDC_EDIT1, str);
            wsprintf(str, _T("%d 원"), player2.getMoney());
            SetDlgItemText(hWnd, IDC_EDIT2, str);
           
            wsprintf(str, _T("플레이어 %d 턴"),turn);
            SetDlgItemText(hWnd, IDC_EDIT7, str);
            
            SelectObject(mem1dc, oldBit1);
            DeleteDC(mem1dc);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

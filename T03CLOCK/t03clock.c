/* FILE NAME: t03clock.c
 * PROGRAMMER: YM5
 * DATE 02.06.2022
 * PURPOSE: Write a programm which would show a clock
 */

#include <stdlib.h>
#include <windows.h>
#include <math.h>

/* Main window class name */
#define WND_CLASS_NAME "My window class"

/* Forward declarartion */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam );
VOID DrawHands( HDC hDC, INT X, INT Y, DOUBLE angle, INT LEN, INT len );

/* Draw eye function */
/* VOID DrawHand( HDC hDC, INT X, INT Y, DOUBLE angle, INT len ); */

/* Main program function */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;
  HBRUSH hbr;

  hbr = CreateSolidBrush(RGB(220, 150, 150));

  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = hbr;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIcon = LoadIcon(NULL, IDI_ERROR);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
    return 0;
  }

  hWnd = CreateWindow(WND_CLASS_NAME, "Title", WS_OVERLAPPEDWINDOW, 30, 30, 1000, 1000, NULL, NULL, hInstance, NULL);

  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
} /* End of 'WinMain' function */

/* Main window message handle function */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  SYSTEMTIME st;
  BITMAP bm;
  SIZE sz;
  HBRUSH hBr, hOldBr;
  HFONT hFnt, hFntOld;
  CHAR Buf [102];
  INT BufLen;
  static CHAR *wDays[] = {"ом", "бр", "яп", "вр", "ор", "яа", "бя"};
  static INT w, h;
  static HDC hMemDC;
  static HDC hMemDC1;
  static HBITMAP hBm;
  static HBITMAP hBm1;

  switch (Msg)
  {
  case WM_CREATE:
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    hMemDC1 = CreateCompatibleDC(hDC);
    hBm1 = LoadImage(NULL, "clockface.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC1, hBm1);
    SetTimer(hWnd, 30, 30, NULL);
    return 0;

  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, w, h);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC, hBm);

    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;

  case WM_TIMER:

    /* draw background */
    hBr = CreateSolidBrush(RGB(220, 30, 220));
    hOldBr = SelectObject(hMemDC, hBr);

    GetObject(hBm1, sizeof(BITMAP), &bm);
    BitBlt(hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, hMemDC1, 0, 0, SRCCOPY);
    SetStretchBltMode(hMemDC, COLORONCOLOR);
    StretchBlt(hMemDC, 0, 0, w, h, hMemDC1, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

    /* output time */
    GetLocalTime(&st);

    /* draw hands */
    DrawHands(hMemDC, w / 2, h / 2, st.wHour * (3.14159265359 / 6), 100, 10);
    DrawHands(hMemDC, w / 2, h / 2, st.wMinute * (3.14159265359 / 30), 200, 10);
    DrawHands(hMemDC, w / 2, h / 2, st.wSecond * (3.14159265359 / 30), 300, 10);

    /* add text to screen */
    hFnt = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
      RUSSIAN_CHARSET,
      OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
      VARIABLE_PITCH | FF_SCRIPT, "Consolas");                                                
    hFntOld = SelectObject(hMemDC, hFnt);
    SetTextColor(hMemDC, RGB(0, 0, 0));
    SetBkColor(hMemDC, RGB(220, 220, 180));
    SetBkMode(hMemDC, TRANSPARENT);

    BufLen = wsprintf(Buf, "%02d.%02d.%d %02d:%02d:%02d", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);
    GetTextExtentPoint(hMemDC, Buf, BufLen, &sz);
    TextOut(hMemDC, (w - sz.cx) / 2, 60, Buf, BufLen);
    SelectObject(hMemDC, hFntOld);
    DeleteObject(hFnt);

    /* copy back buffer to screen */
    hDC = GetDC(hWnd);
    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    ReleaseDC(hWnd, hDC);
    return 0;

  case WM_DESTROY:
    if (hBm != NULL)
      DeleteObject(hBm);
    DeleteDC(hMemDC);
    KillTimer(hWnd, 30);
    PostQuitMessage(30);
    return 0;
  }

  return DefWindowProc(hWnd, Msg, wParam, lParam);
}


/* Draw hands function */
/* VOID DrawHand( HDC hDC, INT X, INT Y, DOUBLE angle, INT len )
{
  SelectObject(hDC, GetStockObject(DC_PEN));
  SetDCPenColor(hDC, BLACK_PEN);

  MoveToEx(hDC, X, Y, NULL);
  LineTo(hDC, X + sin(angle) * len, Y - cos(angle) * len);

  SelectObject(hDC, GetStockObject(DC_PEN));
  SetDCPenColor(hDC, BLACK_PEN);

  MoveToEx(hDC, X + sin(angle) * len, Y - cos(angle) * len, NULL);
  LineTo(hDC, X + sin(angle) * len + cos(2 * 3.14159265359 / 3 + angle), Y - cos(angle) * len + sin(2 * 3.14159265359 / 3 + angle)); */

/* DrawHandsFunction */
VOID DrawHands( HDC hDC, INT X, INT Y, DOUBLE angle, INT LEN, INT len )
{
  POINT pnts[4] =
  {
    {X + (INT)(sin(angle) * LEN), Y - (INT)(cos(angle) * LEN)},
    {X + (INT)(cos(angle) * len), Y + (INT)(sin(angle) * len)},
    {X - (INT)(sin(angle) * len), Y + (INT)(cos(angle) * len)},
    {X - (INT)(cos(angle) * len), Y - (INT)(sin(angle) * len)}
  };

  Polygon(hDC, pnts, sizeof(pnts) / sizeof(pnts[0]));
}
/* End of 'DrawHands' function */


/* Flip Full Screen Function */ 
VOID FlipFullScreen( HWND hWnd )
{
  static BOOL IsFullScreen = FALSE;
  static RECT SaveRect;
 
  if (!IsFullScreen)
  {
    HMONITOR hmon;
    MONITORINFO mi;
    RECT rc;
 
    /* Save old window size and position */
    GetWindowRect(hWnd, &SaveRect);
 
    /* Go to full screen mode */
 
    /* oBTAIN NEAREST MONITOR */
    hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    mi.cbSize = sizeof(mi);
    GetMonitorInfo(hmon, &mi);
 
    /* Expand window */
    rc = mi.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);
 
    SetWindowPos(hWnd, HWND_TOP,
      rc.left, rc.top,
      rc.right - rc.left,
      rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
  }
  else
  {
    /* Restore from full screen mode */
    SetWindowPos(hWnd, HWND_TOP,
      SaveRect.left, SaveRect.top,
      SaveRect.right - SaveRect.left,
      SaveRect.bottom - SaveRect.top,
      SWP_NOOWNERZORDER);
  }
  IsFullScreen = !IsFullScreen;
} /* End of 'FlipFullScreen' function */

/* END OF 't03clock.c' FILE */
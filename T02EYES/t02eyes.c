/* FILE NAME: t02eyes.c
 * PROGRAMMER: YM5
 * DATE 02.06.2022
 * PURPOSE: WRITE A PROGRAM WHICH WOULD MAKE AN EYE FOLLOW THE MOUSE
 */

#include <stdlib.h>
#include <windows.h>
#include <math.h>

/* Main window class name */
#define WND_CLASS_NAME "My window class"

/* Forward declarartion */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam );

/* Draw eye function */
VOID DrawEye( HDC hDC, INT X, INT Y, INT R, INT R1, INT Mx, INT My );

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
  POINT pt;
  PAINTSTRUCT ps;
  static INT w, h;
  static HDC hMemDC;
  static HBITMAP hBm;

  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 30, NULL);
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    hBm = NULL;
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

    /* clear background */
    SelectObject(hMemDC, GetStockObject(DC_BRUSH));
    SelectObject(hMemDC, GetStockObject(NULL_PEN));
    SetDCBrushColor(hMemDC, RGB(0, 180, 221));
    Rectangle(hMemDC, 0, 0, w, h);

    /* draw eye */
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    DrawEye(hMemDC, w / 2 + 120, h / 2, 90, 30, pt.x, pt.y);
    DrawEye(hMemDC, w / 2 - 120, h / 2, 90, 30, pt.x, pt.y);

    hDC = GetDC(hWnd);
    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    ReleaseDC(hWnd, hDC);
    return 0;

  case WM_DESTROY:
    if (hBm != NULL)
      DeleteObject(hBm);
    DeleteDC(hMemDC);
    KillTimer(hWnd, 30);
    return 0;
  }

  return DefWindowProc(hWnd, Msg, wParam, lParam);
}

/* Draw eye function */
VOID DrawEye( HDC hDC, INT X, INT Y, INT R, INT R1, INT Mx, INT My )
{
  DOUBLE len = sqrt((Mx - X) * (Mx - X) + (My - Y) * (My - Y));

  SetDCBrushColor(hDC, RGB(255, 255, 255));
  SetDCPenColor(hDC, RGB(0, 0, 0));
  Ellipse(hDC, X - R, Y + R, X + R, Y - R);
  
  SetDCBrushColor(hDC, BLACK_BRUSH);
  Ellipse(hDC, X + (INT)((R - R1) * (Mx - X) / len) - R1, Y + (INT)((R - R1) * (My - Y) / len) - R1,
               X + (INT)((R - R1) * (Mx - X) / len) + R1, Y + (INT)((R - R1) * (My - Y) / len) + R1);
} /* End of 'DrawEye' function */

/* END OF 't02eyes.c' FILE */

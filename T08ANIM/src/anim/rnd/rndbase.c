/* FILE NAME: rndbase.c
 * PROGRAMMER : YM5
 * LAST UPDATE : 09.06.2022
 * PURPOSE : 3D animation project.
 *           Startup Module.
 */

#include "rnd.h"

VOID YM5_RndInit( HWND hWnd )
{
  HDC hDC;

  YM5_hRndWnd = hWnd;

  hDC = GetDC(YM5_hRndWnd);
  YM5_hRndDCFrame = CreateCompatibleDC(hDC);
  ReleaseDC(YM5_hRndWnd, hDC);
  /*-- устанваливаем параметры по умолчанию */
  /* set camera */
  YM5_RndCamSet(VecSet(8, 8, 8), VecSet(0, 0, 0), VecSet(0, 1, 0));

}

VOID YM5_RndClose( VOID )
{
  DeleteObject(YM5_hRndBmFrame);
  DeleteDC(YM5_hRndDCFrame);
}

VOID YM5_RndResize( INT W, INT H )
{
  HDC hDC = GetDC(YM5_hRndWnd);

  if (YM5_hRndBmFrame)
    DeleteObject(YM5_hRndBmFrame);
  YM5_hRndBmFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(YM5_hRndWnd, hDC);
  SelectObject(YM5_hRndDCFrame, YM5_hRndBmFrame);

  /* save size */
  YM5_RndFrameW = W;
  YM5_RndFrameH = H;

  /* recalculating projection */
  YM5_RndProjSet();
}

VOID YM5_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, YM5_RndFrameW, YM5_RndFrameH,
    YM5_hRndDCFrame, 0, 0, SRCCOPY);
}

VOID YM5_RndStart( VOID )
{
  SelectObject(YM5_hRndDCFrame, GetStockObject(DC_BRUSH));
  SelectObject(YM5_hRndDCFrame, GetStockObject(NULL_PEN));
  SetDCBrushColor(YM5_hRndDCFrame, RGB(180, 240, 190));
  Rectangle(YM5_hRndDCFrame, 0, 0, YM5_RndFrameW + 1, YM5_RndFrameH + 1);
  SelectObject(YM5_hRndDCFrame, GetStockObject(DC_PEN));
  SetDCPenColor(YM5_hRndDCFrame, RGB(0, 0, 0));
}

VOID YM5_RndEnd( VOID )
{
}

VOID YM5_RndProjSet( VOID )
{
  DBL Wp, Hp;

  Wp = Hp = YM5_RndProjSize;
  if (YM5_RndFrameW > YM5_RndFrameH)
    Wp *= (DOUBLE)YM5_RndFrameW / YM5_RndFrameH;
  else
    Hp *= (DOUBLE)YM5_RndFrameH / YM5_RndFrameW;

  YM5_RndMatrProj = MatrFrustum(-Wp / 2, Wp / 2, -Hp / 2, Hp / 2, YM5_RndProjDist, YM5_RndProjFarClip);
  YM5_RndMatrVP = MatrMulMatr(YM5_RndMatrView, YM5_RndMatrProj);
}

VOID YM5_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  YM5_RndMatrView = MatrView(Loc, At, Up);
  YM5_RndMatrVP = MatrMulMatr(YM5_RndMatrView, YM5_RndMatrProj);
}

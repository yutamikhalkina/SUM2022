/* FILE NAME: anim.c
 * PROGRAMMER : YM5
 * LAST UPDATE : 11.06.2022
 * PURPOSE : 3D animation project.
 *           Startup Module.
 */

#include "anim.h"

ym5ANIM YM5_Anim;

VOID YM5_AnimInit( HWND hWnd )
{
  YM5_Anim.hWnd = hWnd;
  YM5_RndInit(hWnd);
  YM5_Anim.hDC = YM5_hRndDCFrame;

  YM5_TimerInit();
  YM5_AnimInputInit();
}

VOID YM5_AnimClose( VOID )
{
  INT i;

  for (i = 0; i < YM5_Anim.NumOfUnits; i++)
  {
    YM5_Anim.Units[i]->Close(YM5_Anim.Units[i], &YM5_Anim);
    free(YM5_Anim.Units[i]);
    YM5_Anim.Units[i] = NULL;
  }
  YM5_Anim.NumOfUnits = 0;
  YM5_RndClose();
}

VOID YM5_AnimResize( INT W, INT H )
{
  YM5_Anim.W = W;
  YM5_Anim.H = H;
  YM5_RndResize(W, H);
}

VOID YM5_AnimCopyFrame( HDC hDC )
{
  YM5_RndCopyFrame(hDC);
}

VOID YM5_AnimRender( VOID )
{
  INT i;

  /* . . . timer, keyboard, mouse, joystick . . . */
  YM5_TimerResponse();
  YM5_AnimInputResponse();

  for (i = 0; i < YM5_Anim.NumOfUnits; i++)
    YM5_Anim.Units[i]->Response(YM5_Anim.Units[i], &YM5_Anim);

  YM5_RndStart();
  for (i = 0; i < YM5_Anim.NumOfUnits; i++)
    YM5_Anim.Units[i]->Render(YM5_Anim.Units[i], &YM5_Anim);
  YM5_RndEnd();
}

VOID YM5_AnimUnitAdd( ym5UNIT *Uni )
{
  if (YM5_Anim.NumOfUnits < YM5_MAX_UNITS)
    YM5_Anim.Units[YM5_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &YM5_Anim);
}

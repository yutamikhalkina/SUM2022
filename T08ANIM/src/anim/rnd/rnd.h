/* FILE NAME: rnd.h
 * PROGRAMMER : YM5
 * LAST UPDATE : 09.06.2022
 * PURPOSE : 3D animation project.
 *           Startup Module.
 */

#ifndef __rnd_h_
#define __rnd_h_

#include "def.h"

extern HWND YM5_hRndWnd;                 /* Work window handle */
extern HDC YM5_hRndDCFrame;              /* Work window memory device context  */
extern HBITMAP YM5_hRndBmFrame;          /* Work window background bitmap handle */
extern INT YM5_RndFrameW, YM5_RndFrameH; /* Work window size */

extern DBL
  YM5_RndProjSize,     /* Project plane fit square */
  YM5_RndProjDist,     /* Distance to project plane from viewer (near) */
  YM5_RndProjFarClip;  /* Distance to project far clip plane (far) */

extern MATR
  YM5_RndMatrView, /* View coordinate system matrix */
  YM5_RndMatrProj, /* Projection coordinate system matrix */
  YM5_RndMatrVP;   /* Stored (View * Proj) matrix */

typedef struct tagym5VERTEX
{
  VEC P;
} ym5VERTEX;

typedef struct tagym5PRIM
{
  ym5VERTEX *V;
  INT NumOfV;
  INT *I;
  INT NumOfI;

  MATR Trans;
} ym5PRIM;

VOID YM5_RndInit( HWND hWnd );
VOID YM5_RndClose( VOID );
VOID YM5_RndResize( INT W, INT H );
VOID YM5_RndCopyFrame( HDC hDC );
VOID YM5_RndStart( VOID );
VOID YM5_RndEnd( VOID );
VOID YM5_RndProjSet( VOID );
VOID YM5_RndCamSet( VEC Loc, VEC At, VEC Up );
BOOL YM5_RndPrimCreate( ym5PRIM *Pr, INT NoofV, INT NoofI );
VOID YM5_RndPrimFree( ym5PRIM *Pr );
VOID YM5_RndPrimDraw( ym5PRIM *Pr, MATR World );
BOOL YM5_RndPrimLoad( ym5PRIM *Pr, CHAR *FileName );

#endif /* __rnd_h_ */

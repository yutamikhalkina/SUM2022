/* FILE NAME: rnddata.c
 * PROGRAMMER : YM5
 * LAST UPDATE : 09.06.2022
 * PURPOSE : 3D animation project.
 *           Startup Module.
 */

#include "rnd.h"

HWND YM5_hRndWnd;                 /* Work window handle */
HDC YM5_hRndDCFrame;              /* Work window memory device context  */
HBITMAP YM5_hRndBmFrame;          /* Work window background bitmap handle */
INT YM5_RndFrameW, YM5_RndFrameH; /* Work window size */

DBL
  YM5_RndProjSize = 0.1,  /* Project plane fit square */
  YM5_RndProjDist = 0.1,  /* Distance to project plane from viewer (near) */
  YM5_RndProjFarClip = 300;  /* Distance to project far clip plane (far) */

MATR
  YM5_RndMatrView, /* View coordinate system matrix */
  YM5_RndMatrProj, /* Projection coordinate system matrix */
  YM5_RndMatrVP;   /* Stored (View * Proj) matrix */


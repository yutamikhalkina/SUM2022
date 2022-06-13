/* FILE NAME: globe.c
 * PROGRAMMER: YM5
 * DATE 06.06.2022
 * PURPOSE: Draw a globe
 */

#include <stdlib.h>
#include <windows.h>
#include <math.h>

#include "globe.h"
#include "timer.h"

/* Main window class name */
#define WND_CLASS_NAME "My window class"

#define GRID_H 50
#define GRID_W 30

static VEC Geom[GRID_H][GRID_W];

VOID GlobeSet( DBL R )
{
  DOUBLE pi = 3.14159265359;
  INT i, j;

  for (i = 0; i < GRID_H; i++)
    for (j = 0; j < GRID_W; j++)
    {
      DOUBLE theta = i * pi / (GRID_H - 1);
      DOUBLE phi = j * 2 * pi / (GRID_W - 1);

      Geom[i][j].X = R * sin(theta) * sin(phi);
      Geom[i][j].Y = R * cos(theta);
      Geom[i][j].Z = R * sin(theta) * cos(phi);
    }
}

VOID GlobeDraw( HDC hDC, INT w, INT h )
{
  INT i, j, R = 400, s = 3;
  DOUBLE r;
  DOUBLE ProjDist, Size, Wp, Hp;
  POINT ps[4];
  MATR m;
  static POINT pnts[GRID_H][GRID_W];

  /* m = MatrMulMatr(MatrRotateY(45 * GLB_Time),
                  MatrTranslate(VecSet(sin(GLB_Time), 0, 0))); 
     m = MatrIdentity(); */

  r = (w < h ? w : h) / 2;

  ProjDist = Size = 3;
  Wp = Hp = Size;
  if(w > h)
    Wp *= (DOUBLE)w / h;
  else
    Hp *= (DOUBLE)h / w;

  m = MatrMulMatr5(MatrRotate(28 * GLB_Time, VecSet(0, 1, 0)),
                   MatrRotate(45 * sin(GLB_Time), VecSet(1, 0, 0)),
                   MatrTranslate(VecSet(0, fabs(sin(GLB_Time * 2)) - 0.5, 0)),
                   MatrView(VecSet(0, 5 * sin(GLB_Time), 3), VecSet(0, 0, 0), VecSet(0, 1, 0)),
                   MatrFrustum(-Wp / 2, Wp / 2, -Hp / 2, Hp / 2, ProjDist, 500));

  for (i = 0; i < GRID_H; i++)
    for (j = 0; j < GRID_W; j++)
    {
      VEC p = VecMulMatr(Geom[i][j], m);

      pnts[i][j].x = (INT)((p.X * R) + w / 2);
      pnts[i][j].y = (INT)(-(p.Y * R) + h / 2);
    }

  for (i = 0; i < GRID_H; i++)
    for (j = 0; j < GRID_W; j++)
      Ellipse(hDC, pnts[i][j].x - s, pnts[i][j].y - s,
                   pnts[i][j].x + s, pnts[i][j].y + s);
   
  for (j = 0; j < GRID_W; j++)
  {
    MoveToEx(hDC, pnts[0][j].x, pnts[0][j].y, NULL);
    for (i = 1; i < GRID_H; i++)
      LineTo(hDC, pnts[i][j].x, pnts[i][j].y);
  }

  for(i = 1; i < GRID_H; i++)
  {
    MoveToEx(hDC, pnts[i][0].x, pnts[i][0].y, NULL);
    for (j = 0; j < GRID_W; j++)
      LineTo(hDC, pnts[i][j].x, pnts[i][j].y);
  }
  
  for(i = 0; i < GRID_H - 1; i++)
    for (j = 0; j < GRID_W - 1; j++)
    {
      SelectObject(hDC, GetStockObject(DC_BRUSH));
      SetDCPenColor(hDC, RGB(220, 30, 40));
      ps[0] = pnts[i][j];
      ps[1] = pnts[i][j + 1];
      ps[2] = pnts[i + 1][j + 1];
      ps[3] = pnts[i + 1][j];

      if ((ps[0].x - ps[1].x) * (ps[0].y + ps[1].y) +
          (ps[1].x - ps[2].x) * (ps[1].y + ps[2].y) +
          (ps[2].x - ps[3].x) * (ps[2].y + ps[3].y) +
          (ps[3].x - ps[0].x) * (ps[3].y + ps[0].y) <= 0)
         Polygon(hDC, ps, 4);
    }

  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SetDCPenColor(hDC, RGB(40, 40, 40));
  SelectObject(hDC, GetStockObject(DC_PEN));
  SetDCPenColor(hDC, RGB(220, 30, 40));
  for(i = 0; i < GRID_H - 1; i++)
    for (j = 0; j < GRID_W - 1; j++)
    {
      ps[0] = pnts[i][j];
      ps[1] = pnts[i][j + 1];
      ps[2] = pnts[i + 1][j + 1];
      ps[3] = pnts[i + 1][j];

      if ((ps[0].x - ps[1].x) * (ps[0].y + ps[1].y) +
          (ps[1].x - ps[2].x) * (ps[1].y + ps[2].y) +
          (ps[2].x - ps[3].x) * (ps[2].y + ps[3].y) +
          (ps[3].x - ps[0].x) * (ps[3].y + ps[0].y) > 0)
         Polygon(hDC, ps, 4);
    }

}

VEC RotateZ( VEC P, DOUBLE Angle )
{
  VEC NewP;
  DOUBLE pi = 3.14159265359;
  DOUBLE a = Angle * pi / 180, si = sin(a), co = cos(a);
 
  NewP.X = P.X * co - P.Y * si;
  NewP.Y = P.X * si + P.Y * co;
  NewP.Z = P.Z;
  return NewP;
} /* End of 'RotateZ' function */ 

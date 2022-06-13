/* FILE NAME: rndprim.c
 * PROGRAMMER : YM5
 * LAST UPDATE : 09.06.2022
 * PURPOSE : 3D animation project.
 *           Startup Module.
 */

#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "rnd.h"

BOOL YM5_RndPrimCreate( ym5PRIM *Pr, INT NoofV, INT NoofI )
{
  INT size;

  memset(Pr, 0, sizeof(ym5PRIM));
  size = sizeof(ym5VERTEX) * NoofV + sizeof(INT) * NoofI;
  if ((Pr->V = malloc(size)) == NULL)
    return FALSE;
  Pr->I = (INT *)(Pr->V + NoofV);
  Pr->NumOfV = NoofV;
  Pr->NumOfI = NoofI;
  Pr->Trans = MatrIdentity();
  memset(Pr->V, 0, size);
  return TRUE;
}

VOID YM5_RndPrimFree( ym5PRIM *Pr )
{
  if (Pr->V != NULL)
    free(Pr->V);
  memset(Pr, 0, sizeof(ym5PRIM));
}

VOID YM5_RndPrimDraw( ym5PRIM *Pr, MATR World )
{
  INT i;
  MATR wvp = MatrMulMatr3(Pr->Trans, World, YM5_RndMatrVP);
  POINT *pnts;

  if ((pnts = malloc(Pr->NumOfV * sizeof(POINT))) == NULL)
    return;

  /* Build projection */
  for (i = 0; i < Pr->NumOfV; i++)
  {
    VEC p = VecMulMatr(Pr->V[i].P, wvp);

    pnts[i].x = (INT)((p.X + 1) * YM5_RndFrameW / 2);
    pnts[i].y = (INT)((-p.Y + 1) * YM5_RndFrameH / 2);
  }

  for (i = 0; i < Pr->NumOfI; i += 3)
  {
    MoveToEx(YM5_hRndDCFrame, pnts[Pr->I[i]].x, pnts[Pr->I[i]].y, NULL);
    LineTo(YM5_hRndDCFrame, pnts[Pr->I[i + 1]].x, pnts[Pr->I[i + 1]].y);
    LineTo(YM5_hRndDCFrame, pnts[Pr->I[i + 2]].x, pnts[Pr->I[i + 2]].y);
    LineTo(YM5_hRndDCFrame, pnts[Pr->I[i]].x, pnts[Pr->I[i]].y);
  }

  free(pnts);
}

BOOL YM5_RndPrimLoad( ym5PRIM *Pr, CHAR *FileName )
{
  FILE *F;
  INT nv = 0, nind = 0;
  static CHAR Buf[1000];

  memset(Pr, 0, sizeof(ym5PRIM));
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count vertexes and indexes */
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0, i;

      for (i = 1; Buf[i] != 0; i++)
        if (isspace((UCHAR)Buf[i - 1]) &&!isspace((UCHAR)Buf[i]))
          n++;
      nind += (n - 2) * 3;
    }

  /* Create primitive */
  if (!YM5_RndPrimCreate(Pr, nv, nind))
  {
    fclose(F);
    return FALSE;
  }

  /* Load primitive */
  rewind(F);
  nv = nind = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;
      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      Pr->V[nv++].P = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0, i, nc, n0, n1;
	
      for (i = 1; Buf[i] != 0; i++)
        if (isspace((UCHAR)Buf[i - 1]) &&!isspace((UCHAR)Buf[i]))
        {
          sscanf(Buf + i, "%d", &nc);
          if (n == 0)
            n0 = nc;
          else if (n == 1)
            n1 = nc;
          else
          {
            Pr->I[nind++] = n0 - 1;
            Pr->I[nind++] = n1 - 1;
            Pr->I[nind++] = nc - 1;
            n1 = nc;
          }
          n++;
        }
    }
  fclose(F);
  return TRUE;
} /* End of 'YM5_RndPrimLoad' function */

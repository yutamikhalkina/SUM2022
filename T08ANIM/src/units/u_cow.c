/* FILE NAME  : u_cow.c
 * PROGRAMMER : YM5
 * LAST UPDATE: 11.06.2022
 * PURPOSE    : 3D animation project.
 *              Common declaration module.
 */

#include <time.h>

#include "ym5.h"

typedef struct
{
  YM5_UNIT_BASE_FIELDS;
  VEC Pos;
  ym5PRIM Cow;
} ym5UNIT_COW;

static VOID YM5_UnitInit( ym5UNIT_COW *Uni, ym5ANIM *Ani )
{
  /* load cow.obj */
  YM5_RndPrimLoad(&Uni->Cow, "bin/models/cow.obj");
}

static VOID YM5_UnitClose( ym5UNIT_COW *Uni, ym5ANIM *Ani )
{
  YM5_RndPrimFree(&Uni->Cow);
}

static VOID YM5_UnitRender( ym5UNIT_COW *Uni, ym5ANIM *Ani )
{
  /* draw cow */
  YM5_RndPrimDraw(&Uni->Cow, MatrMulMatr(MatrScale(VecSet(0.1, 0.1, 0.1)), MatrRotate(47 * Ani->Time, VecSet(1, 2, 3))));
}

static VOID YM5_UnitResponse( ym5UNIT_COW *Uni, ym5ANIM *Ani )
{
}


ym5UNIT * YM5_AnimUnitCreateCow( VOID )
{
  ym5UNIT *Uni;

  if ((Uni = YM5_AnimUnitCreate(sizeof(ym5UNIT_COW))) == NULL)
    return NULL;
  Uni->Init = (VOID *)YM5_UnitInit;
  Uni->Close = (VOID *)YM5_UnitClose;
  Uni->Render = (VOID *)YM5_UnitRender;
  Uni->Response = (VOID *)YM5_UnitResponse;

  return Uni;
}

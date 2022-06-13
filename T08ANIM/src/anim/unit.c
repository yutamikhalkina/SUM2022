/* FILE NAME: unit.c
 * PROGRAMMER : YM5
 * LAST UPDATE : 09.06.2022
 * PURPOSE : 3D animation project.
 *           Unit handle module.
 */

#include "anim.h"

static VOID YM5_UnitInit( ym5UNIT *Uni, ym5ANIM *Ani )
{
}

static VOID YM5_UnitClose( ym5UNIT *Uni, ym5ANIM *Ani )
{
}

static VOID YM5_UnitResponse( ym5UNIT *Uni, ym5ANIM *Ani )
{
}

static VOID YM5_UnitRender( ym5UNIT *Uni, ym5ANIM *Ani )
{
}

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (ym5UNIT *) pointer to created unit.
 */
ym5UNIT * YM5_AnimUnitCreate( INT Size )
{
  ym5UNIT *Uni;

  /* Memory allocation */
  if (Size < sizeof(ym5UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);

  /* Setup unit methods */
  Uni->Init = YM5_UnitInit;
  Uni->Close = YM5_UnitClose;
  Uni->Response = YM5_UnitResponse;
  Uni->Render = YM5_UnitRender;

  return Uni;
} /* End of 'YM5_AnimUnitCreate' function */

/* FILE NAME  : anim.h
 * PROGRAMMER : YM5
 * LAST UPDATE: 11.06.2022
 * PURPOSE    : 3D animation project.
 *              Animation system declaration module.
 */

#ifndef __anim_h_
#define __anim_h_

#include "rnd/rnd.h"

typedef struct tagym5UNIT ym5UNIT;
typedef struct tagym5ANIM ym5ANIM;

#define YM5_UNIT_BASE_FIELDS \
  VOID (*Init)( ym5UNIT *Uni, ym5ANIM *Ani );      \
  VOID (*Close)( ym5UNIT *Uni, ym5ANIM *Ani );     \
  VOID (*Response)( ym5UNIT *Uni, ym5ANIM *Ani );  \
  VOID (*Render)( ym5UNIT *Uni, ym5ANIM *Ani )

struct tagym5UNIT
{
  YM5_UNIT_BASE_FIELDS;
};

#define YM5_MAX_UNITS 3000
struct tagym5ANIM
{
  HWND hWnd;
  HDC hDC;
  INT W, H;

  ym5UNIT *Units[YM5_MAX_UNITS];
  INT NumOfUnits;

  DBL
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per second value */
  BOOL
    IsPause;                     /* Pause flag */

  BYTE
    Keys[256],
    KeysClick[256];

  INT Mx, My, Mz, Mdx, Mdy, Mdz;

  BYTE
    JBut[32], JButClick[32]; /* Joystick button states */
  INT JPov;                  /* Joystick point-of-view control [-1,0..7] */
  DBL
    JX, JY, JZ, JR;                       /* Joystick axes */

};

extern ym5ANIM YM5_Anim;

VOID YM5_AnimInit( HWND hWnd );
VOID YM5_AnimClose( VOID );
VOID YM5_AnimResize( INT W, INT H );
VOID YM5_AnimCopyFrame( HDC hDC );
VOID YM5_AnimRender( VOID );

VOID YM5_AnimUnitAdd( ym5UNIT *Uni );

ym5UNIT * YM5_AnimUnitCreate( INT Size );

VOID YM5_TimerInit( VOID );
VOID YM5_TimerResponse( VOID );

VOID YM5_AnimInputInit( VOID );
VOID YM5_AnimInputResponse( VOID );

#endif /* __anim_h_ */

/* END OF 'anim.h' FILE */

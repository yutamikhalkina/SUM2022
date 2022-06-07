/* FILE NAME: globe.h
 * PROGRAMMER: YM5
 * DATE 06.06.2022
 * PURPOSE: Draw a globe
 */

#include <windows.h>

typedef DOUBLE DBL;

typedef struct
{
  DBL X, Y, Z;
} VEC;

VOID GlobeSet( DBL R );
VOID GlobeDraw( HDC hDc, INT w, INT h );

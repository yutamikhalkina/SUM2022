/* Mikhalkina Yuta, 10-5, 01.06.2022 */

#include <stdio.h>
#include <windows.h>

void main( void )
{
  int x = 30;
  char Buf[100];

  scanf("%i", &x);
  sprintf(Buf, "x = %i", x);
  MessageBox(NULL, Buf, "caption", MB_OK | MB_ICONINFORMATION);
}
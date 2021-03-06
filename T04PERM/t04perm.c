/* FILE NAME: t04perm.c
 * PROGRAMMER: YM5
 * DATE: 04.06.2022
 * PURPOSE: Permutation output.
 */

#include <stdio.h>
#include <windows.h>

/* Permutation array */
#define MAX 5
INT P[MAX];
BOOL IsParity; 

/* Store permutation to log file function */
VOID Store( VOID )
{
  FILE *F;
  int i;

  F = fopen("PERM.TXT", "a");
  if (F == NULL)
    return;
  for (i = 0; i < MAX - 1; i++)
    fprintf(F, "%d,", P[i]);
  fprintf(F, "%d – parity: %s\n", P[MAX - 1], IsParity ? "even" : "odd");
 
  fclose(F);
} /* End of 'Store' function */

VOID Swap( INT *A, INT *B )
{
  INT tmp = *A;
 
  *A = *B;
  *B = tmp;
}


VOID Go( INT Pos )
{
  INT i;

  if (Pos == MAX)
    Store();
  else
  {
    for (i = Pos; i < MAX; i++)
    {
      if (Pos != i)
        IsParity = !IsParity;
      Swap(&P[Pos], &P[i]);
      Go(Pos + 1);
      if (Pos != i)
        IsParity = !IsParity;
      Swap(&P[Pos], &P[i]);
    }
  }
}
 
VOID main( VOID )
{
  INT i;
  
  for (i = 0; i < MAX; i++)
    P[i] = i + 1;
  IsParity = TRUE;
  Go(0);
}

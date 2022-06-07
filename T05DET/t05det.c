 /* FILE NAME: t05det.c
 * PROGRAMMER: YM5
 * DATE: 04.06.2022
 * PURPOSE: Permutation output.
 */

#include <stdio.h>
#include <windows.h>

typedef DOUBLE DBL;
 
#define MAX 10
DBL A[MAX][MAX];
INT N;
FLOAT Det;
 
INT P[MAX];
BOOL IsParity;
 
BOOL LoadMatrix( CHAR *FileName )
{
  FILE *F;
  INT i;
  INT j;
 
  N = 0;
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;
  fscanf(F, "%d", &N);
  if (N > MAX)
    N = MAX;
  else
    if (N < 0)
      N = 0;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      fscanf(F, "%lf", &A[i][j]);
  fclose(F);
  return TRUE;
}

VOID Swap( INT *A, INT *B )
{
  INT tmp = *A;
 
  *A = *B;
  *B = tmp;
}

VOID Go( INT Pos )
{
  INT i;
  DOUBLE prod;

   if (Pos == N)
  {
    for (i = 0, prod = 1; i < N; i++)
      prod *= A[i][P[i]];
    Det += prod * (IsParity ? 1 : -1);
  }
  else
  {
    for (i = Pos; i < N; i++)
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
  
  LoadMatrix("in.txt");
  for (i = 0; i < N; i++)
    P[i] = i;
  IsParity = TRUE;
  Go(0);
  
  printf("%f", Det);

  getchar();
}
/* FILE NAME: t06detg.c
 * PROGRAMMER: YM5
 * DATE: 04.06.2022
 * PURPOSE: Permutation output.
 */

#include <stdio.h>
#include <windows.h>
#include <math.h>

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

VOID Swap( DBL *A, DBL *B )
{
  DBL tmp = *A;
 
  *A = *B;
  *B = tmp;
}

DBL DetG( VOID )
{
  INT i, x, y, max_row, max_col;
  DBL det;

  det = 1;
  for (i = 0; i < N; i++)
  {
    /* look for maximum matrix element */
    max_row = max_col = i;
    for (y = i; y < N; y++)
      for (x = i; x < N; x++)
        if (fabs(A[y][x]) > fabs(A[max_row][max_col]))
          max_row = y, max_col = x;
    if (A[max_row][max_col] == 0)
    {
      det = 0;
      break;
    }
    if (max_row != i)
    {
      /* Swap max_row and i row (elements/columns: [i..N-1]) */
      for (x = i; x < N; x++)
        Swap(&A[max_row][x], &A[i][x]);
      det = -det;
    }
   
    if (max_col != i)
    {
      /* Swap max_col and i column (elements/columns: [0..N-1]) */
      // ???
      det = -det;
    }
    /* Subtrack from every row k:[i+1..N-1] row [i] multipled by (A[k][i] / A[i][i]) */
    // ???
    det *= A[i][i];
  }
  return det;
}

VOID main( VOID )
{
  int x, y;

  LoadMatrix("in.txt");
  printf("Source matrix\n");
  for (y = 0; y < N; y++)
  {
    for (x = 0; x < N; x++)
      printf(" %10.3f", A[y][x]);
    printf("\n");
  }
  printf("Determinant: %f\n", DetG());
}

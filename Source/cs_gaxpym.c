/* 20150412 */
/* Tim.D. book, ex2.27 */
/* Y = A * X + Y */
/* X, Y is dense matrix */
/* 3 versions: [1] X, Y col major */
/*             [2] X, Y row major */
/*             [3] X, Y col major but operate 32 col at a time */
/* paramters: major: COL, ROW, COL1 */
/*            M: row # of Y */
/*            N: col # of A */
/*            K: col # of Y */
/* running time comparison for m=3000, n=6000, K=1000: */
/* [1]: 100%      [2] 90%      [3] 139% */
#include "cs.h"
#define COL		0
#define ROW		1
#define COL1	2
csi *cs_gaxpym(int major, csi M, csi N, csi K,
              cs *A, double *X, double *Y)
{
	if (!CS_CSC(A) || !X || !Y)
	{
		printf("input bad, quit\n") ; return 0 ;
	}
	if (A->m != M || A->n != N)
	{
		printf("input size bad, quit\n") ; return 0 ;
	}
	csi m, n, j, p, k, d = 32, g ;
	csi *Ai, *Ap ;
	double *Ax ;
	m = A->m ; n = A->n ; Ai = A->i ; Ap = A->p ; Ax = A->x ;
	if (major == COL)
	{
		for (k=0; k<K; k++)
		{
			for (j=0; j<n; j++)
			{
				for (p=Ap[j]; p<Ap[j+1]; p++)
				{
					Y[k*m + Ai[p]] += Ax[p] * X[k*n + j] ;
				}
			}
		}	
	}
	else if (major == ROW)
	{
		for (j=0; j<n; j++)
		{
			for (p=Ap[j]; p<Ap[j+1]; p++)
			{
				for (k=0; k<K; k++)
				{
					Y[Ai[p]*K + k] += Ax[p] * X[j*K + k] ;
				}
			}
		}
	}
	else if (major == COL1)
	{
		for (g=0; g<K/d; g++)
		{
			for (j=0; j<n; j++)
			{
				for (p=Ap[j]; p<Ap[j+1]; p++)
				{
					for (k=0; k<d; k++)
					{
						Y[Ai[p] + m*(g*d+k)] += Ax[p] * X[j + n*(g*d+k)] ;
					}
				}
			}
		}
		for (j=0; j<n; j++)
		{
			for (p=Ap[j]; p<Ap[j+1]; p++)
			{
				for (k=g*d; k<K; k++)
				{
					Y[Ai[p] + k*m] += Ax[p] * X[j + k*n] ;
				}
			}
		}
	}
	return 1 ;
}

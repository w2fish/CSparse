/* 20150404 */
/* Tim.D. book, ex2.16 */
/* create sparse matrix copy of dense matrix in col major form */
#include "cs.h"
cs *cs_spcolm(double *D, csi m, csi n)
{
	cs *A = NULL ;
	csi j, p, t, *Ai, *Ap ;
	double *Ax ;
	A = cs_spalloc(m, n, m*n, 1, 0) ;
	if (!A) return NULL ;
	Ai = A->i ; Ap = A->p ; Ax = A->x ;
	/* copy D to A */
	Ap[0] = 0 ;
	for(j=0; j<n; j++)
	{
		Ap[j+1] = Ap[j] + m ;
		for(p=Ap[j],t=0; p<Ap[j+1]; p++,t++)
		{
			Ai[p] = t ;
			Ax[p] = D[p] ;
		}
	}
	return A ;
}

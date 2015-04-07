/* 20150407 */
/* Tim.D. book, ex2.25 */
/* cs version of matlab statement A(i, j) = C */
/* where i, j are integer vectors */
/* Currently, i, j does NOT contain duplicate indices */
/* because I can NOT figure out how i, j has duplicate indices */
#include "cs.h"
cs *cs_subm3(cs *A, cs *C, int *iv, int il, int *jv, int jl)
{
	if (!CS_CSC(A) || !CS_CSC(C) || !iv || !jv)
	{
		printf("input bad, quit\n") ; return NULL ;
	}
	if (C->m != il || C->n != jl)
	{
		printf("input size wrong, quit\n") ; return NULL ;
	}
	cs *D = NULL ;  /* the output matrix */
	csi m, n, i, j, p, nz = 0 ;
	csi *Ai, *Ap, *Ci, *Cp, *Di, *Dp ;
	double *Ax, *Cx, *Dx ;
	int a, b ;
	/* find m and n for D */
	for (a=0; a<il; a++)
	{
		b = iv[a] ; 
		m = CS_MAX(A->m, b) ;
	}
	for (a=0; a<jl; a++)
	{
		b = jv[a] ; 
		n = CS_MAX(A->n, b) ;
	}
	/* allocate D */
	D = cs_spalloc(m, n, m + n, 1, 0) ;
	Dp = D->p ;
	/* copy A and C to D */
	for (j=0; j<n; j++)
	{
		if (nz + m > D>nzmax && !cs_sprealloc(D, 2*D->nzmax+m))
		{
			printf("reallocate D fail, quit\n") ;
			return cs_done(D, w, NULL, 0) ;
		}
		Di = D->i ; Dx = D->x ;
		Dp[j] = nz ;
		for (



	


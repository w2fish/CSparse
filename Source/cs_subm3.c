/* 20150408 */
/* Tim.D. book, ex2.25 */
/* cs version of matlab statement A(i, j) = C */
/* where i, j are integer vectors */
/* i, j may or may not contain duplicate indices */
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
	csi m, n, i, j, p, nz = 0, t, s, r ;
	csi *Ai, *Ap, *Ci, *Cp, *Di, *Dp, *w, *iw, *jw ;
	double *Ax, *Cx, *Dx, *x ;
	int a, b ;
	Ai = A->i ; Ap = A->p ; Ax = A->x ;
	Ci = C->i ; Cp = C->p ; Cx = C->x ;
	/* find m and n for D */
	m = A->m ;
	for (a=0; a<il; a++)
	{
		b = iv[a] ; 
		m = CS_MAX(m, b+1) ;
	}
	n = A->n ;
	for (a=0; a<jl; a++)
	{
		b = jv[a] ; 
		n = CS_MAX(n, b+1) ;
	}
	/* allocate D */
	D = cs_spalloc(m, n, m + n, 1, 0) ;
	w = cs_calloc(m, sizeof(csi)) ;
	iw = cs_calloc(C->m, sizeof(csi)) ;
	jw = cs_calloc(n, sizeof(csi)) ;
	x = cs_malloc(m, sizeof(double)) ;
	Dp = D->p ;
	/* initialize workspace */
	for (i=0; i<C->m; i++) iw[i] = -1 ;
	for (j=0; j<n; j++) jw[j] = -1 ;
	/* set iw, match row index of C to D */
	for (a=0; a<il; a++)
	{
		iw[a] = iv[a] ;
	}
	/* set jw, match col index of D to C */
	p = 0 ;
	for (a=0; a<jl; a++)
	{
		jw[jv[a]] = p++ ;
	}
	/* copy A and C to D */
	for (j=0; j<n; j++)
	{
		if (nz + m > D->nzmax && !cs_sprealloc(D, 2*D->nzmax+m))
		{
			printf("reallocate D fail, quit\n") ;
			iw = cs_free(iw) ;
			jw = cs_free(jw) ;
			x = cs_free(x) ;
			return cs_done(D, w, NULL, 0) ;
		}
		Di = D->i ; Dx = D->x ;
		Dp[j] = nz ;
		/* copy j-th col of A to D */
		if (j < A->n)
		{
			for (p=Ap[j]; p<Ap[j+1]; p++)
			{
				i = Ai[p] ;
				w[i] = j + 1 ;
				Di[nz++] = i ;
				x[i] = Ax[p] ;
			}
		}
		/* copy t-th col of C to D */
		if (jw[j] != -1)
		{
			t = jw[j] ;  /* col index in C */
			for(s=Cp[t]; s<Cp[t+1]; s++)
			{
				r = iw[Ci[s]] ;  /* row index in D */
				if (w[r] < j + 1)
				{
					w[r] = j + 1 ;
					Di[nz++] = r ;
				}
				x[r] = Cx[s] ;
			}
	 	}
		for (p=Dp[j]; p<nz ; p++) Dx[p] = x[Di[p]] ;
	}
	Dp[n] = nz ;
	cs_sprealloc(C, 0) ;
	/* release */
	w = cs_free(w) ;
	iw = cs_free(iw) ;
	jw = cs_free(jw) ;
	x = cs_free(x) ;
	
	return D ;
}

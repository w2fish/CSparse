/* 20150407 */
/* Tim.D. book, ex2.24 */
/* cs version of matlab statement C = A(i, j) */
/* where i, j are integer vectors */
/* i, j may OR may not contain duplicate indices */
#include "cs.h"
cs *cs_subm2(cs *A, int *iv, int il, int *jv, int jl)
{
	if (!CS_CSC(A) || !iv || !jv)
	{
		printf("input bad, quit\n") ; return NULL ;
	}
	cs *C = NULL ;
	csi m, n, i, j, p, t, s, nz = 0 ;
	csi *Ai, *Ap, *Ci, *Cp, *w ;
	double *Ax, *Cx ;
	Ai = A->i ; Ap = A->p ; Ax = A->x ;
	m = il ; n = jl ;
	/* allocate C and w */
	w = cs_calloc(A->m, sizeof(csi)) ;
	C = cs_spalloc(m, n, m + n, 1, 0) ;
	if (!C || !w)
	{
		printf("allocate C or w fail, quit\n") ; 
		return cs_done(C, w, NULL, 0) ;
	}
	Cp = C->p ;
	printf("allocate C done\n") ;
	/* copy A to C */
	for (t=0; t<A->m; t++) w[t] = -1 ;
	for (t=0; t<n; t++)
	{
		if (nz + m > C->nzmax && !cs_sprealloc(C, 2*C->nzmax+m))
		{
			printf("reallocate C fail, quit\n") ;
			return cs_done(C, w, NULL, 0) ;
		}
		Ci = C->i ; Cx = C->x ;
		j = jv[t] ;  /* col index */
		for (p=Ap[j]; p<Ap[j+1]; p++)
		{
			w[Ai[p]] = p ;  /* match row # to p */
		}
		Cp[t] = nz ;
		for (s=0; s<m; s++)
		{
			i = iv[s] ; /* row index */
			if (w[i] != -1)
			{
				Ci[nz] = i ;
				Cx[nz++] = Ax[w[i]] ;
			}
		}
		for (p=Ap[j]; p<Ap[j+1]; p++)
		{
			w[Ai[p]] = -1 ;  /* initialize w */
		}
	}
	Cp[n] = nz ;
	cs_sprealloc(C, 0) ;
	return cs_done(C, w, NULL, 1) ;
}	

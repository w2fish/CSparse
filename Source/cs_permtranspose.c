/* 20150410 */
/* Tim.D. book, ex2.26 */
/* cs version of matlab statement C = A(p,q)' */
/* combing cs_permute and cs_transpose */
/* p, q are permutation vectors */
#include "cs.h"
cs *cs_permtranspose(const cs *A, const csi *pinv, const csi *qinv, csi values)
{
	if (!CS_CSC(A))
	{
		printf("input A bad, quit\n") ; return NULL ;
	}
	cs *C = NULL ;
	csi m, n, j, p, k, q, t ;
	csi *Ai, *Ap, *Ci, *Cp, *w ;
	double *Ax, *Cx ;
	m = A->m ; n = A->n ; Ai = A->i ; Ap = A->p ; Ax = A->x ;
	/* allocate C and workspace w */
	C = cs_spalloc(n, m, Ap[n], values && Ax != NULL, 0) ;
	w = cs_calloc(m, sizeof(csi)) ;
	if (!C || !w)
	{
		printf("allocate C or w fail, quit\n") ; 
		return cs_done(C, w, NULL, 0) ;
	}
	Ci = C->i ; Cp = C->p ; Cx = C->x ;
	/* count entry # in each row of A, match to C */
	for (p=0; p<Ap[n]; p++) 
	{
		w [ pinv ? pinv[Ai[p]] : Ai[p] ] ++ ;
	}
	cs_cumsum(Cp, w, m) ;
	/* copy A to C */
	for (j=0; j<n; j++)
	{
		k = qinv ? qinv[j] : j ; /* col j of A is col qinv[k] of A(p,q) */
		for (p=Ap[j]; p<Ap[j+1]; p++)
		{
			t = pinv ? pinv[Ai[p]] : Ai[p] ; /* row Ai[p] of A is row */
							 /* pinv[Ai[p]] of A(p,q) */
			Ci[q = w[t]++] = k ;
			if (values) Cx[q] = Ax[p] ;
		}
	}
	/* return */
	return cs_done(C, w, NULL, 1) ;
}



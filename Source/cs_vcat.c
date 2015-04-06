/* 20150406 */
/* Tim.D. book, ex2.22 */
/* cs version of matlab statement C = [A; B] */
#include "cs.h"
cs *cs_vcat(const cs *A, const cs *B)
{
	if (!CS_CSC(A) || !CS_CSC(B))
	{
		printf("input bad, quit\n") ; return NULL ;
	}
	/* # of col must equal */
	if (A->n != B->n)
	{
		printf("A, B not same # of col, quit\n") ; return NULL ;
	}
	cs *C = NULL ;
	csi j, p, t = 0, m, n, am, bm, nz, value ;
	csi *Ci, *Cp , *Ai, *Ap, *Bi, *Bp ;
	double *Ax, *Bx, *Cx ;
	am = A->m ; Ai = A->i ; Ap = A->p ; Ax = A->x ;
	bm = B->m ; Bi = B->i ; Bp = B->p ; Bx = B->x ;
	n = A->n ; m = am + bm ; nz = Ap[n] + Bp[n] ;
	value = (Ax != NULL) && (Bx != NULL) ;
	/* allocate C */
	C = cs_spalloc(m, n, nz, value, 0) ;
	if (!C)
	{
		printf("allocate C fail, quit\n") ; 
		return cs_done(C, NULL, NULL, 0) ;
	}
	Ci = C->i ; Cp = C->p ; Cx = C->x ;
	/* copy A and B to C */
	for (j=0; j<n; j++)
	{
		Cp[j] = Ap[j] + Bp[j] ;
		for (p=Ap[j]; p<Ap[j+1]; p++)
		{
			Ci[t] = Ai[p] ;
			if (value) Cx[t] = Ax[p] ;
			t++ ;
		}
		for (p=Bp[j]; p<Bp[j+1]; p++)
		{
			Ci[t] = Bi[p] ;
			if (value) Cx[t] = Bx[p] ;
			t++ ;
		}
	}
	Cp[n] = nz ;
	return C ;
}


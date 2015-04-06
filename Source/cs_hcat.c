/* 20150406 */
/* Tim.D. book, ex2.22 */
/* cs version of matlab statement C = [A B] */
#include "cs.h"
cs *cs_hcat(const cs *A, const cs *B)
{
	if (!CS_CSC(A) || !CS_CSC(B))
	{
		printf("input bad, quit\n") ; return NULL ;
	}
	/* # of row must equal */
	if (A->m != B->m)
	{
		printf("A, B not same # of row, quit\n") ; return NULL ;
	}
	cs *C = NULL ;
	csi j, p, m, n, an, bn, anz, nz, value ;
	csi *Ci, *Cp , *Ai, *Ap, *Bi, *Bp ;
	double *Ax, *Bx, *Cx ;
	an = A->n ; Ai = A->i ; Ap = A->p ; Ax = A->x ; anz = Ap[an] ;
	bn = B->n ; Bi = B->i ; Bp = B->p ; Bx = B->x ;
	m = A->m ; n = an + bn ; nz = Ap[an] + Bp[bn] ;
	value = (Ax != NULL) && (Bx != NULL) ;
	/* allocate C */
	C = cs_spalloc(m, n, nz, value, 0) ;
	if (!C)
	{
		printf("allocate C fail, quit\n") ; 
		return cs_done(C, NULL, NULL, 0) ;
	}
	Ci = C->i ; Cp = C->p ; Cx = C->x ;
	/*printf("C = \n") ; cs_print(C, 0) ;*/
	/* copy A to C */
	for (j=0; j<an; j++)
	{
		Cp[j] = Ap[j] ;
		for (p=Ap[j]; p<Ap[j+1]; p++)
		{
			Ci[p] = Ai[p] ;
			if (value) Cx[p] = Ax[p] ;
		}
	}
	Cp[an] = Ap[an] ;
	/* copy B to C */
	for (j=0; j<bn; j++)
	{
		Cp[j+an+1] = anz + Bp[j+1] ;
		for (p=Bp[j]; p<Bp[j+1]; p++)
		{
			Ci[anz+p] = Bi[p] ;
			if (value) Cx[anz+p] = Bx[p] ;
		}
	}
	return C ;
}

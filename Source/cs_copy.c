/* 20150403 */
/* Tim.D. book, ex2.14 */
/* return a copy of A */
#include "cs.h"
cs *cs_copy(cs *A)
{
	cs *C = NULL ;
	csi m, n, j, p, *Ai, *Ap, *Ci, *Cp ;
	double *Ax, *Cx ;
	if (!A) return NULL ;
	m = A->m ; n = A->n ; Ai = A->i ; Ap = A->p ; Ax = A->x ;
	C = cs_spalloc(m, n, Ap[n], Ax != NULL, 0) ;
	if (!C) return NULL ;
	Ci = C->i ; Cp = C->p ; Cx = C->x ;
	for(j=0; j<=n; j++)
	{
		Cp[j] = Ap[j] ;
	}
	for(j=0; j<n; j++)
	{
		for(p=Ap[j]; p<Ap[j+1]; p++)
		{
			Ci[p] = Ai[p] ;
			if (Cx) Cx[p] = Ax[p] ;
		}
	}
	return C ;
}
	

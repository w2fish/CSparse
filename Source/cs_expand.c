/* convert triplet form to CSC */
#include "cs.h"
cs *cs_expand(cs *A)
{
	cs *T ;
	csi m, n, p, j, nzmax, *Ap, *Ai, *Tp, *Ti ;
	double *Ax, *Tx ;
	if(!CS_CSC(A)) return NULL ;
	m = A->m ; n = A->n ; Ap = A->p ; Ai = A->i ; Ax = A->x ; nzmax = A->nzmax ;
	T = cs_spalloc(m, n, nzmax, Ax != NULL, 1) ;
	if(!T) return cs_done(T, NULL, NULL, 0) ;
	Tp = T->p ; Ti = T->i ; Tx = T->x ;
	for(j=0; j<n; j++)
	{
		for(p=Ap[j]; p<Ap[j+1]; p++)
		{
			Ti[p] = Ai[p] ;
			Tp[p] = j ;
			Tx[p] = Ax[p] ;
		}
	}
	T->nz = p ;
	return T ;
}
	

	

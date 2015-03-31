/* 20150331 */
/* Tim.D. book, ex2.6 */
/* transpose cs matrix in triplet form in O(1) time */
#include "cs.h"
cs *cs_transpose_triplet(const cs *T, csi values)
{
	cs *C ;
	csi p, m, n, nz, nzmax, *Ti, *Tp, *Ci, *Cp ;
	double *Tx, *Cx ;
	if(!CS_TRIPLET(T)) return NULL ;
	m = T->m ; n = T->n; nzmax = T->nzmax ; nz = T->nz ;
	Ti = T->i ; Tp = T->p ; Tx = T->x ;
	C = cs_spalloc(m, n, nzmax, values && Tx, 1) ;
	Ci = C->i ; Cp = C->p ; Cx = C->x ; C->nz = nz ;
	if(!C) return cs_done(C, NULL, NULL, 0) ;
	for(p=0; p<nz; p++)
	{
		Ci[p] = Tp[p] ;
		Cp[p] = Ti[p] ;
		Cx[p] = Tx[p] ;
	}
	return C ;
}

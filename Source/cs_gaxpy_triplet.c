/* 20150402 */
/* Tim.D. book, ex2.10 */
/* y = T*x+y */
/* triplet matrix multiply a dense vector */
#include "cs.h"
csi cs_gaxpy_triplet(const cs *T, const double *x, double *y)
{
	csi i, j, p, nz, *Ti, *Tp, ok ;
	double *Tx ;
	if(!CS_TRIPLET(T) || !x || !y)
	{
		printf("input bad, quit\n") ;
		return 0 ;
	}
	nz = T->nz ;
	Ti = T->i ; Tp = T->p ; Tx = T->x ;
	for(p=0; p<nz; p++)
	{
		i = Ti[p] ;
		j = Tp[p] ;
		y[i] += Tx[p] * x[j] ;
	}
	return 1;
}

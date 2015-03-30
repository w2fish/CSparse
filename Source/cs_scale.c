/* 20150330 */
/* overwrite A with RAC, where R and C is diagonal */
#include "cs.h"
void cs_scale(cs *A, double *r, double *c)
{
	csi j, n, p, *Ap, *Ai ;
	double *Ax ;
	if(!CS_CSC(A) || !(A->x)) 
	{
		printf("A is bad, quit\n") ;
		return ;
	}
	Ap = A->p ; 
	Ai = A->i ;
	Ax = A->x ;
	n = A->n ;
	for(j=0; j<n; j++)
	{
		for(p=Ap[j]; p<Ap[j+1]; p++)
		{
			Ax[p] *= r[Ai[p]] * c[j] ;
		}
	}
	return ;
}

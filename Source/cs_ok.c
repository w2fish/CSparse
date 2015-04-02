/* 20150403 */
/* Tim.D. book, ex2.12 */
/* check if matrix is ok and optionally print */
/* [1] if values < 0, A->x ignored, otherwise, A->x non-NULL */
/* [2] if sorted is true, columns must be sorted */
/* [3] if values > 0, no numerically zeros in A */
#include "cs.h"
int cs_ok(cs *A, int sorted, int values, int print)
{
	csi n, j, p, t, *Ai, *Ap ;
	double *Ax ;
	int flag = 1 ;
	if (!CS_CSC(A)) return 0 ; /* check input */
	n = A->n ; Ai = A->i ; Ap = A->p ; Ax = A->x ;
	
	/* print */
	if (print) cs_print(A, 0) ;

	/* check if Ax is non-NULL */
	if (values >= 0 && !A->x) return 0 ;
	
	/* check if A is sorted */
	if (sorted) 
	{
		for(j=0; j<n; j++)
		{
			for(p=Ap[j]; p<Ap[j+1]; p++)
			{
				t = p - 1 ; /* element before p */
				if (t < Ap[j]) continue; /* check boundary */
				if (Ai[t] <= Ai[p]) continue;
				else return 0 ;
			}
		}
	}

	/* check if any numerically zeros in A */
	if (values > 0)
	{
		for(j=0; j<n; j++)
		{
			for(p=Ap[j]; p<Ap[j+1]; p++)
			{
				if (Ax[p] == 0) return 0 ;
			}
		}
	}

	return 1 ;
}

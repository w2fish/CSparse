/* 20150404 */
/* utility function */
/* check if row index of CSC matrix is sorted */
#include "cs.h"
int cs_issorted(cs *A)
{
	/* check input */
	if (!A)
	{
		printf("A NULL, quit\n") ; return 0 ;
	}
	csi m, n, j, p, t, *Ai, *Ap ;
	n = A->n ; Ai = A->i ; Ap = A->p ;
	/* check row index */
	for(j=0; j<n; j++)
	{
		for(p=Ap[j]+1; p<Ap[j+1]; p++)
		{
			t = p - 1 ;
			if (Ai[t] > Ai[p]) return 0 ;
		}
	}
	return 1 ;
}


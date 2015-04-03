/* 20150403 */
/* Tim.D. book, ex2.13 */
#include "cs.h"
int cs_issym(cs *A)
{
	cs *C = NULL;
	csi m, n, p, j, *Ai, *Ap, *Ci, *Cp ;
	double *Ax, *Cx ;
	if (!CS_CSC(A)) 
	{
		printf("A is bad, quit\n") ; return 0 ;
	}
	m = A->m ; n = A->n ; Ai = A->i ; Ap = A->p ; Ax = A->x ;
	if (m != n)
	{
		printf(" m != n, quit\n") ; return 0 ;
	}
	/* C = A' */
	C = cs_transpose(A, 1) ;
	if (!C)
	{
		printf("transpose of A fail, quit\n") ; return 0 ;
	}
	Ci = C->i ; Cp = C->p ; Cx = C->x ;
	/*printf("C = \n") ; cs_print(C, 0) ;*/
	/* check C == A ? */
	for(j=0; j<n; j++)
	{
		if (Ap[j+1] != Cp[j+1]) return 0 ; /* check # of entry in col */
	}
	for(j=0; j<n; j++)
	{
		for(p=Ap[j]; p<Ap[j+1]; p++)
		{
			/*if (Ai[p] == j) continue ;  skip diagonal */
			if (Ai[p] != Ci[p]) return 0 ; /* check row index */
			if (Ax[p] != Cx[p]) return 0 ; /* check value */
		}
	}
	/* release */
	cs_spfree(C) ;

	return 1 ;
}

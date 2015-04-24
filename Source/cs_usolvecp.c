/* 20150419 */
/* Tim.D. book, ex3.6 */
/* solve Ux=b where x and b are dense.  x=b on input, solution on output. */
/* another version of cs_usovle that cols of U is permuted */
/* last entry in each col has the largest row index */
#include "cs.h"
csi cs_usolvecp(const cs *U, double *x)
{
	if (!CS_CSC(U) || !x)
	{
		printf("input bad, quit\n") ; return 0 ;
	}
	csi j, p, k, n ;
	csi *Ui = NULL, *Up = NULL ;
	csi *w = NULL ;
	double *Ux = NULL ;
	n = U->n ; Ui = U->i ; Up = U->p ; Ux = U->x ;
	/* allocate workspace w, length n */
	w = cs_malloc(n, sizeof(csi)) ;
	if (!w)
	{
		printf("allocate w fail, quit\n") ; return 0 ;
	}
	/* find out col index, put in w */
	for (j=0; j<n; j++)
	{
		k = Ui[Up[j+1]-1] ; /* diagonal entry */
		w[k] = j ; /* old col k permuted to col j */
	}
	/* solve U * x = b */
	for (k=n-1; k>=0; k--)
	{
		j = w[k] ;
		x[k] /= Ux[Up[j+1]-1] ;
		for (p=Up[j]; p<Up[j+1]-1; p++)
		{
			x[Ui[p]] -= x[k] * Ux[p] ;
		}
	}
	/* release */
	w = cs_free(w) ;

	return 1 ;
}


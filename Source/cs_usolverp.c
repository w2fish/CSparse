/* 20150419 */
/* Tim.D. book, ex3.4 */
/* solve Ux=b where x and b are dense.  x=b on input, solution on output. */
/* another version of cs_usovle that rows of U is permuted */
#include "cs.h"
csi cs_usolverp(const cs *U, double *x)
{
	if (!CS_CSC(U) || !x)
	{
		printf("input bad, quit\n") ; return 0 ;
	}
	csi j, p, n ;
	csi *Ui = NULL, *Up = NULL ;
	csi *w = NULL, *v = NULL ;
	double *Ux = NULL ;
	n = U->n ; Ui = U->i ; Up = U->p ; Ux = U->x ;
	/* allocate workspace w, length n */
	w = cs_malloc(n, sizeof(csi)) ;
	v = cs_calloc(n, sizeof(csi)) ;
	if (!w || !v)
	{
		printf("allocate w or v fail, quit\n") ; return 0 ;
	}
	for (j=0; j<n; j++) w[j] = -1 ; /* initialize w to -1 */
	/* find out diagonal entry in each col, put in w */
	for (j=0; j<n; j++)
	{
		for (p=Up[j]; p<Up[j+1]; p++)
		{
			if (!v[Ui[p]])
			{
				if (w[j] < 0) 
				{
					w[j] = p ;
					v[Ui[p]] = 1 ;
				}
				else
				{
					printf("too much entries in col %d in U, quit\n", (int)j) ;
					w = cs_free(w) ;
					v = cs_free(v) ;
					return 0 ;
				}
			}
		}
		if (w[j] < 0)
		{
			printf("too few entries in col %d in U, quit\n", (int)j) ;
			w = cs_free(w) ;
			v = cs_free(v) ;
			return 0 ;
		}
	}
	/* solve U * x = b */
	for (j=n-1; j>=0; j--)
	{
		x[j] /= Ux[w[j]] ;
		for (p=Up[j]; p<Up[j+1]; p++)
		{
			if (p != w[j])
			{
				x[Ui[p]] -= x[j] * Ux[p] ;
			}
		}
	}
	/* release */
	w = cs_free(w) ;
	v = cs_free(v) ;

	return 1 ;
}

/* 20150418 */
/* Tim.D. book, ex3.3 */
/* solve Lx=b where x and b are dense.  x=b on input, solution on output. */
/* another version of cs_lsovle that rows of L is permuted */
#include "cs.h"
csi cs_lsolverp(const cs *L, double *x)
{
	if (!CS_CSC(L) || !x)
	{
		printf("input bad, quit\n") ; return 0 ;
	}
	csi j, p, n ;
	csi *Li = NULL, *Lp = NULL ;
	csi *w = NULL, *v = NULL ;
	double *Lx = NULL ;
	n = L->n ; Li = L->i ; Lp = L->p ; Lx = L->x ;
	/* allocate workspace w, length n */
	w = cs_malloc(n, sizeof(csi)) ;
	v = cs_calloc(n, sizeof(csi)) ;
	if (!w || !v)
	{
		printf("allocate w or v fail, quit\n") ; return 0 ;
	}
	for (j=0; j<n; j++) w[j] = -1 ; /* initialize w to -1 */
	/* find out diagonal entry in each col, put in w */
	for (j=n-1; j>=0; j--)
	{
		for (p=Lp[j]; p<Lp[j+1]; p++)
		{
			if (!v[Li[p]])
			{
				if (w[j] < 0) 
				{
					w[j] = p ;
					v[Li[p]] = 1 ;
				}
				else
				{
					printf("too much entries in col %d in L, quit\n", (int)j) ;
					w = cs_free(w) ;
					v = cs_free(v) ;
					return 0 ;
				}
			}
		}
		if (w[j] < 0)
		{
			printf("too few entries in col %d in L, quit\n", (int)j) ;
			w = cs_free(w) ;
			v = cs_free(v) ;
			return 0 ;
		}
	}
	/* solve L * x = b */
	for (j=0; j<n; j++)
	{
		x[j] /= Lx[w[j]] ;
		for (p=Lp[j]; p<Lp[j+1]; p++)
		{
			if (p != w[j])
			{
				x[Li[p]] -= x[j] * Lx[p] ;
			}
		}
	}
	/* release */
	w = cs_free(w) ;
	v = cs_free(v) ;

	return 1 ;
}

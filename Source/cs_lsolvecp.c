/* 20150419 */
/* Tim.D. book, ex3.5 */
/* solve Lx=b where x and b are dense.  x=b on input, solution on output. */
/* another version of cs_lsovle that cols of L is permuted */
/* 1st entry in each col has the smallest row index */
#include "cs.h"
csi cs_lsolvecp(const cs *L, double *x)
{
	if (!CS_CSC(L) || !x)
	{
		printf("input bad, quit\n") ; return 0 ;
	}
	csi j, p, k, n ;
	csi *Li = NULL, *Lp = NULL ;
	csi *w = NULL ;
	double *Lx = NULL ;
	n = L->n ; Li = L->i ; Lp = L->p ; Lx = L->x ;
	/* allocate workspace w, length n */
	w = cs_malloc(n, sizeof(csi)) ;
	if (!w)
	{
		printf("allocate w fail, quit\n") ; return 0 ;
	}
	/* find out col index, put in w */
	for (j=0; j<n; j++)
	{
		p = n - (Lp[j+1] - Lp[j]) ;
		if (p > n)
		{
			printf("too few entry in col %d, quit\n", (int)j) ; return 0 ;
		}
		w[p] = j ;
	}
	/* solve L * x = b */
	for (k=0; k<n; k++)
	{
		j = w[k] ;
		x[k] /= Lx[Lp[j]] ;
		for (p=Lp[j]+1; p<Lp[j+1]; p++)
		{
			x[Li[p]] -= x[k] * Lx[p] ;
		}
	}
	/* release */
	w = cs_free(w) ;

	return 1 ;
}


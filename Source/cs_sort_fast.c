/* 20150331 */
/* Tim.D. book, ex2.8 */
/* sort cs matrix column-wise by qsort */
/* the original matrix is WRITTEN by sorted matrix */
/* speed: SAME as cs_sort_slow, LOWER than cs_sort */
#include "cs.h"
cs *cs_sort_fast(cs *A)
{
	csi maxCol = 0, p, j, t, n, *Ai, *Ap ;
	double *Ax ;
	double *w = NULL ;
	n = A->n ;
	Ai = A->i ; Ap = A->p ; Ax = A->x ;
	/* check input */
	if(!CS_CSC(A) || !Ax)
	{
		printf("A bad, quit\n") ;
		return A ;
	}
	/* find max # of element in col */
	for(j=0; j<n; j++)
	{
		t = Ap[j+1] - Ap[j] ;
		maxCol = maxCol > t ? maxCol : t ;
	}
	/* allocate work space w */
	w = (double *)malloc(sizeof(double) * 2 * maxCol) ;
	if(!w) 
	{
		printf("malloc fail, quit\n") ;
		return A ;
	}
	/* sort each col by qsort */
	for(j=0; j<n; j++)
	{
		/* copy col to w */
		for(t=0,p=Ap[j]; p<Ap[j+1]; p++)
		{
			w[t++] = (double)Ai[p] ;
			w[t++] = Ax[p] ;
		}
		t /= 2 ; /* t = Ap[j+1] - Ap[j] */
		qsort(w, t, sizeof(double)*2, compare_double) ;
		/* copy w back to col */
		for(t=0,p=Ap[j]; p<Ap[j+1]; p++)
		{
			Ai[p] = (csi)w[t++] ;
			Ax[p] = w[t++] ;
		}
	}
	/* release */
	if(w) free(w) ;

	return A ;
}

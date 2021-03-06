/* 20150331 */
/* Tim.D. book, ex2.8 */
/* sort cs matrix column-wise by qsort */
/* the original matrix is UNCHANGED */
/* speed: SAME as cs_sort_fast, LOWER than cs_sort */
#include "cs.h"
cs *cs_sort_slow(const cs *A)
{
	cs *S ;
	csi maxCol = 0, p, j, t, m, n, *Ai, *Ap, *Si, *Sp ;
	double *Ax, *Sx ;
	double *w = NULL ;
	n = A->n ; m = A->m ;
	Ai = A->i ; Ap = A->p ; Ax = A->x ;
	/* check input */
	if(!CS_CSC(A) || !Ax)
	{
		printf("A bad, quit\n") ;
		return A ;
	}
	/* allocate for S */
	S = cs_spalloc(m, n, Ap[n], Ax, 0) ;
	if(!S)
	{
		printf("allocate S fail, quit\n") ;
		return A ;
	}
	Si = S->i ; Sp = S->p ; Sx = S->x ;
	for(j=0; j<=n; j++)
	{
		Sp[j] = Ap[j] ;
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
			Si[p] = (csi)w[t++] ;
			Sx[p] = w[t++] ;
		}
	}
	/* release */
	if(w) free(w) ;

	return S ;
}

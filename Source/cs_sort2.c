/* 20150402 */
/* Tim.D. book, ex2.11 */
/* sort cs matrix column-wise by 2 transpose, this is really cool */
/* in 2nd transpose, avoid extra work compared to cs_sort */
#include "cs.h"
cs *cs_sort2(cs *A)
{
	cs *C = NULL, *D = NULL ;
	csi m, n, p, q, j, *Ai, *Ap, *Ci, *Cp, *Di, *Dp, *w ;
	csi ok ;
	const csi values = 1 ;
	double *Ax, *Cx, *Dx ;
	if(!CS_CSC(A)) return NULL ;
	Ai = A->i ; Ap = A->p ; Ax = A->x ; m = A->m ; n = A->n ; 
	/* 1st transpose */
	C = cs_spalloc(n, m, Ap[n], values && Ax, 0) ;
	w = cs_calloc(m, sizeof(csi)) ; /* work space */
	if(!C || !w) return cs_done(C, w, NULL, 0) ;
	Ci = C->i ; Cp = C->p ; Cx = C->x ;
	for(p=0; p<Ap[n]; p++) w[Ai[p]]++ ; /* count row */
	cs_cumsum(Cp, w, m) ;
	for(j=0; j<n; j++)
	{
		for(p=Ap[j]; p<Ap[j+1]; p++)
		{
			Ci[q = w[Ai[p]]++] = j ;
			if(Cx) Cx[q] = Ax[p] ;
		}
	}
	/*printf("1st transpose finished\n") ;*/
	/* 2nd transpose */
	D = cs_spalloc(m, n, Ap[n], values && Ax, 0) ;
	w = cs_realloc(w, n, sizeof(csi), &ok) ;
	if(!D || !w) 
	{
		printf("allocate D or w fail, quit\n") ;
		return cs_done(D, w, NULL, 0) ;
	}
	Di = D->i ; Dp = D->p ; Dx = D->x ;
	for(j=0; j<n; j++) Dp[j] = w[j] = Ap[j] ;
	Dp[n] = Ap[n] ;
	for(j=0; j<m; j++)
	{
		for(p=Cp[j]; p<Cp[j+1]; p++)
		{
			Di[q = w[Ci[p]]++] = j ;
			if(Dx) Dx[q] = Cx[p] ;
		}
	}
	/* release */
	/*printf("release...\n") ;*/
	cs_spfree(C) ;
	cs_free(w) ;
	/*printf("release done\n") ;*/
	/*return cs_done(D, w, NULL, 1) ;*/
	return D ;
}

/* 201507010 */
/* Tim.D. book, ex4.3 */
/* solve Lx = b */
/* L, x, b are sparse, L comes from Cholesky factorization */
/* the elimination tree is known, pass as parameter*/
#include <stdlib.h>
#include "cs.h"
cs* cs_lsolvesp(const cs *L, const cs *b, csi *parent)
{
	cs *x = NULL ;
	csi n, p, i, len, top ;
	csi *s = NULL, *w = NULL ;
	csi *Lp = NULL, *Li = NULL, *bp = NULL, *bi = NULL ;
	csi *xp = NULL, *xi = NULL ;
	double lki ;
	double *Lx = NULL, *bx = NULL, *xx = NULL ;
	double *xd = NULL ;
	if (!CS_CSC(L) || !CS_CSC(b)) return NULL ;
	n = L->n ; Lp = L->p ; Li = L->i ; Lx = L->x ;
	bp = b->p ; bi = b->i ; bx = b->x ;
	s = cs_malloc(n, sizeof(csi)) ;
	w = cs_malloc(n, sizeof(csi)) ;
	xd = cs_calloc(n, sizeof(double)) ;
	if (!s || !w || !xd) return NULL ;
	for (p=0 ; p<n ; p++) w[p] = Lp[p] ;
	top = n ;
	/* find non-zero pattern of x */
	for (p=bp[0] ; p<bp[1] ; p++)
	{
		i = bi[p] ;
		xd[i] = bx[p] ; /* convert x to dense form */
		for (len=0 ; !CS_MARKED(w,i) ; i = parent[i])
		{
			if (i == -1) break ;
			s[len++] = i ;
			CS_MARK(w, i) ;
		}
		while(len > 0) s[--top] = s[--len] ;
	}
	for (p=top ; p < n ; p++) CS_MARK(w, s[p]) ;	
	x = cs_spalloc(n, 1, n-top, 1, 0) ; /* allocata x */
	if (!CS_CSC(x)) return NULL ;
	xp = x->p ; xi = x->i ; xx = x->x ;
	xp[0] = 0 ; xp[1] = n-top ;
	/* triangular solve */
	csi count = 0 ;
	for ( ; top < n ; top++)
	{
		i = s[top] ;
		lki = xd[i] / Lx[Lp[i]] ;
		xd[i] = lki ;
		for (p=Lp[i]+1 ; p < Lp[i+1] ; p++)
		{
			xd[Li[p]] -= Lx[p] * lki ;
		}
		xi[count] = i ;
		xx[count++] = lki ;
	}
	/* release */
	w = cs_free(w) ;
	s = cs_free(s) ; 
	xd = cs_free(xd) ;

	return x ;
}












/* 20150706 */
/* Tim.D. book, ex4.1 */
/* Another version of cs_ereach to implement O(L) time algorithm */
/* compute e-tree, # of entry in each row/col */
/* use only A and O(n) additional workspace */
/* do NOT modify A */
#include <stdlib.h>
#include "cs.h"
csi cs_ereach2 (const cs *A, csi k, csi *parent, csi *s, \
               csi *w, csi *rc, csi *cc)
{
	csi i, p, n, len, top, *Ap, *Ai ;
	if (!CS_CSC (A) || !parent || !s || !w || !rc || !cc) return -1 ;
	top = n = A->n ; Ap = A->p ; Ai = A->i ;
	CS_MARK (w, k) ;
	for (p=Ap[k] ; p<Ap[k+1] ; p++)
	{
		i = Ai[p] ;
		if (i > k) continue ;
		for (len=0; !CS_MARKED(w,i) ; i=parent[i])
		{
			if (parent[i] == -1) parent[i] = k ;
			s[len++] = i ;
			CS_MARK(w, i) ;
			cc[i]++ ; /* i-th col count */
		}
		while (len > 0) s[--top] = s [--len] ;
	}
	for (p=top ; p<n ; p++) CS_MARK(w, s[p]) ;
	rc[k] = n - top ;
	CS_MARK (w, k) ;
	return (top) ;
}

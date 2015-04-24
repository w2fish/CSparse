/* 20150424 */
/* Tim.D. book, ex3.8 */
/* another version of cs_lsolve, reduce time if b has zero entries */
/* solve Lx=b where x and b are dense.  x=b on input, solution on output. */
/* It turns out time saved by cs_lsolve2 really depends on how many x[j] is
   still ZERO during calculation, varies from
   0%: when the first few b[j] is nonzero to
   100%: when the last few b[j] is nonzero  */
#include "cs.h"
csi cs_lsolve2 (const cs *L, double *x)
{
	csi p, j, n, *Lp, *Li ;
	double *Lx ;
	if (!CS_CSC (L) || !x) return (0) ;                     /* check inputs */
	n = L->n ; Lp = L->p ; Li = L->i ; Lx = L->x ;
	for (j = 0 ; j < n ; j++)
	{
		if (x [j] != 0)
		{
			x [j] /= Lx [Lp [j]] ;
			for (p = Lp [j]+1 ; p < Lp [j+1] ; p++)
			{
				x [Li [p]] -= Lx [p] * x [j] ;
			}
		}
	}
	return (1) ;
}

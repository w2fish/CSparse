/* 20150405 */
/* Tim.D. book, ex2.19 */
/* x = x + beta * A(:,j), where x is a dense vector and A(:,j) is sparse */
/* it is improved version of cs_scatter, since this function is called many
   times for the same j, so to make it more efficient,
   compared to cs_scatter, it checks whether it is called the 1st time for
   this j, if yes, then no need to check if w[i] < mark */
#include "cs.h"
csi cs_scatter2 (const cs *A, csi j, double beta, csi *w, double *x, csi mark,
    cs *C, csi nz, int init)
{
    csi i, p, *Ap, *Ai, *Ci ;
    double *Ax ;
    if (!CS_CSC (A) || !w || !CS_CSC (C)) return (-1) ;     /* check inputs */
    Ap = A->p ; Ai = A->i ; Ax = A->x ; Ci = C->i ;
	if (init)
	{
		for (p = Ap [j] ; p < Ap [j+1] ; p++)
		{
			i = Ai [p] ;                            /* A(i,j) is nonzero */
			w [i] = mark ;                      /* i is new entry in column j */
			Ci [nz++] = i ;                     /* add i to pattern of C(:,j) */
			if (x) x [i] = beta * Ax [p] ;      /* x(i) = beta*A(i,j) */
		}
	}
	else
	{
		for (p = Ap [j] ; p < Ap [j+1] ; p++)
		{
			i = Ai [p] ;                            /* A(i,j) is nonzero */
			if (w [i] < mark)
			{
				w [i] = mark ;                      /* i is new entry in column j */
				Ci [nz++] = i ;                     /* add i to pattern of C(:,j) */
				if (x) x [i] = beta * Ax [p] ;      /* x(i) = beta*A(i,j) */
			}
			else if (x) x [i] += beta * Ax [p] ;    /* i exists in C(:,j) already */
		}
	}
    return (nz) ;
}

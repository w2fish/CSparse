#include "cs.h"
/* y = A*x+y, A is symmetric, only upper triangle stored */
csi cs_gaxpy_symm (const cs *A, const double *x, double *y)
{
    csi p, j, n, *Ap, *Ai ;
    double *Ax ;
    if (!CS_CSC (A) || !x || !y) return (0) ;       /* check inputs */
    n = A->n ; Ap = A->p ; Ai = A->i ; Ax = A->x ;
    for (j = 0 ; j < n ; j++)
    {
        for (p = Ap [j] ; p < Ap [j+1] ; p++)
        {
            y [Ai [p]] += Ax [p] * x [j] ;
            if(j != Ai[p])
			{
           		y [j] += Ax [p] * x [Ai[p]] ;
            }
        }
    }
    return (1) ;
}

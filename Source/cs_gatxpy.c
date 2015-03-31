#include "cs.h"
/* y = (A')*x+y */
csi cs_gatxpy (const cs *A, const double *x, double *y)
{
    csi p, j, n, *Ap, *Ai ;
    double *Ax ;
    if (!CS_CSC (A) || !x || !y) return (0) ;       /* check inputs */
    n = A->n ; Ap = A->p ; Ai = A->i ; Ax = A->x ;
    for (j = 0 ; j < n ; j++)
    {
        for (p = Ap [j] ; p < Ap [j+1] ; p++)
        {
<<<<<<< HEAD
            /* y [j] += Ax [p] * x [Ap[j]] ; */
            y [j] += Ax [p] * x [Ai[p]] ;
=======
            y [j] += Ax [p] * x [Ap[j]] ;
>>>>>>> 2bf6615f0b36fdcc8d712bfd6fd96eb37dbac007
        }
    }
    return (1) ;
}


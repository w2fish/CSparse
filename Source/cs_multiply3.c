/* 20150405 */
/* Tim.D. book, ex2.20 */
/* another version of cs_multiply, use 2 passed */
/* 1st pass: count # of entry in each col of C */
/* 2nd pass: do multiplication */
/* it turns out much slower than cs_multiply */
#include "cs.h"
/* C = A*B */
cs *cs_multiply3 (const cs *A, const cs *B)
{
    csi p, j, i, t, nz = 0, cnz = 0, *Cp, *Ci, *Bp, m, n, *w, values, *Bi ;
	csi *Ai, *Ap ;
    double *x, *Bx, *Cx ;
    cs *C ;
    if (!CS_CSC (A) || !CS_CSC (B)) return (NULL) ;      /* check inputs */
    if (A->n != B->m) return (NULL) ;
    m = A->m ; Ap = A->p ; Ai = A->i ;
    n = B->n ; Bp = B->p ; Bi = B->i ; Bx = B->x ; 
    w = cs_calloc (m, sizeof (csi)) ;                    /* get workspace */
    values = (A->x != NULL) && (Bx != NULL) ;
    x = values ? cs_malloc (m, sizeof (double)) : NULL ; /* get workspace */
	for (j = 0 ; j < n ; j++)
	{
		for (p = Bp [j] ; p < Bp [j+1] ; p++)
		{
			for (t = Ap [Bi [p]] ; t < Ap [Bi [p] + 1] ; t++)
			{
				i = Ai [t] ;
				if (w [i] < j + 1)  
				{
					w [i] = j + 1 ;
					nz++ ;
				}
			}
		}
	}
    C = cs_spalloc (m, n, nz, values, 0) ;        /* allocate result */
    if (!C || !w || (values && !x)) return (cs_done (C, w, x, 0)) ;
    Cp = C->p ; Ci = C->i ; Cx = C->x ;
	for (i = 0 ; i < m ; i++) w [i] = 0 ; /* reset w for 2nd pass */
    for (j = 0 ; j < n ; j++)
    {
        Cp [j] = cnz ;                   /* column j of C starts here */
        for (p = Bp [j] ; p < Bp [j+1] ; p++)
        {
            cnz = cs_scatter (A, Bi [p], Bx ? Bx [p] : 1, w, x, j+1, C, cnz) ;
        }
        if (values) for (p = Cp [j] ; p < cnz ; p++) Cx [p] = x [Ci [p]] ;
    }
    Cp [n] = cnz ;                       /* finalize the last column of C */
    return (cs_done (C, w, x, 1)) ;     /* success; free workspace, return C */
}

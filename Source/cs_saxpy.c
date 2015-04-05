/* 20150405 */
/* Tim.D. book, ex2.21 */
/* cs_saxpy is */
/* another version of cs_add, takes on initialized workspace (w, x) */
/* as input, computes the result, and return the workspace ready for */
/* subsequent call to cs_saxpy */
#include "cs.h"
cs *cs_saxpy(const cs *A, const cs *B, double alpha, double beta, 
			 csi *w, double *x)
{
    csi p, j, nz = 0, anz, *Cp, *Ci, *Bp, m, n, bnz, values ;
    double *Bx, *Cx ;
    cs *C ;
    if (!CS_CSC (A) || !CS_CSC (B)) return (NULL) ;         /* check inputs */
    if (A->m != B->m || A->n != B->n) return (NULL) ;
    m = A->m ; anz = A->p [A->n] ;
    n = B->n ; Bp = B->p ; Bx = B->x ; bnz = Bp [n] ;
    values = (A->x != NULL) && (Bx != NULL) ;
    C = cs_spalloc (m, n, anz + bnz, values, 0) ;           /* allocate result*/
    if (!C || !w || (values && !x)) return (cs_done (C, w, x, 0)) ;
    Cp = C->p ; Ci = C->i ; Cx = C->x ;
    for (j = 0 ; j < n ; j++)
    {
        Cp [j] = nz ;                   /* column j of C starts here */
        nz = cs_scatter (A, j, alpha, w, x, j+1, C, nz) ;   /* alpha*A(:,j)*/
        nz = cs_scatter (B, j, beta, w, x, j+1, C, nz) ;    /* beta*B(:,j) */
        if (values) for (p = Cp [j] ; p < nz ; p++) Cx [p] = x [Ci [p]] ;
    }
    Cp [n] = nz ;                       /* finalize the last column of C */
    cs_sprealloc (C, 0) ;               /* remove extra space from C */
	for (j = 0 ; j < m ; j++)
	{
		w [j] = 0 ;						/* set w back to initial value */
	}
    return (cs_done (C, NULL, NULL, 1)) ;     /* success; free workspace, return C */
}	

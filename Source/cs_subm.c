/* 20150406 */
/* Tim.D. book, ex2.23 */
/* cs version of matlab statement C = A(i1:i2, j1:j2) */
#include "cs.h"
cs *cs_subm(const cs *A, csi i1, csi i2, csi j1, csi j2)
{
	if (!CS_CSC(A))
	{
		printf("A bad, quit\n") ; return NULL ;
	}
	cs *C = NULL ;
	csi m, n, j, cj, p, nz = 0, *Ai, *Ap, *Ci, *Cp ;
	csi il, ih, jl, jh ;
	double *Ax, *Cx ;
	Ai = A->i ; Ap = A->p ; Ax = A->x ;
	/* calculate # of row, col of C */
	il = i1 > i2 ? i2 : i1 ;
	ih = i1 > i2 ? i1 : i2 ;
	jl = j1 > j2 ? j2 : j1 ;
	jh = j1 > j2 ? j1 : j2 ;
	m = ih - il + 1;
	n = jh - jl + 1 ;
	/* allocate C */
	C = cs_spalloc(m, n, 1, 1, 0) ;
	if (!C) 
	{
		printf("allocate C fail, quit\n") ; return cs_done(C, NULL, NULL, 0) ;
	}
	/* copy A to C */
	Cp = C->p ;
	for (j=jl; j<=jh; j++)
	{
		/*printf("m = %d\tC->nzmax = %d\tj = %d\n", (int)m, (int)C->nzmax, (int)j) ;*/
		if (nz + m > C->nzmax && !cs_sprealloc(C, 2*(C->nzmax)+m))
		{
			printf("reallocate C fail, quit\n") ; 			
			return cs_done(C, NULL, NULL, 0) ;
		}
		Ci = C->i ;  Cx = C->x ;  /* Ci and Cx may be reallocated */
		cj = j - jl ;
		Cp[cj] = nz ;
		for (p=Ap[j]; p<Ap[j+1]; p++)
		{
			if (Ai[p] >= il && Ai[p] <= ih)
			{
				/*printf("p = %d\n", (int)p) ;*/
				Ci[nz] = Ai[p] ;
				Cx[nz++] = Ax[p] ;
			}
		}
	}
	Cp[n] = nz ;
	cs_sprealloc(C, 0) ;
	return C ;
}

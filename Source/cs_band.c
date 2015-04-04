/* 20150403 */
/* Tim.D. book, ex2.15 */
/* remove entries outside of diagonal k1 to k2 */
#include "cs.h"
static csi cs_inband(csi l, csi h, csi i, csi j, void *other)
{
	return (i-j >= l && i-j <= h) ;
}
csi cs_band(cs *A, csi k1, csi k2)
{
	csi n, j, p, nz = 0, *Ai, *Ap ;
	double *Ax ;
	if (!CS_CSC(A)) return -1 ;
	csi l = k1 > k2 ? k2 : k1 ; /* lower bound */
	csi h = k1 > k2 ? k1 : k2 ; /* upper bound */
	n = A->n ; Ai = A->i ; Ap = A->p ; Ax = A->x ;
	for(j=0; j<n; j++)
	{
		p = Ap[j] ;
		Ap[j] = nz ;
		for(; p<Ap[j+1]; p++)
		{
			if (cs_inband(l, h, Ai[p], j, NULL))
			{
				if (Ax) Ax[nz] = Ax[p] ;
				Ai[nz++] = Ai[p] ;
			}
		}
	}
	Ap[n] = nz ;
	cs_sprealloc(A, 0) ;
	return nz ;
}


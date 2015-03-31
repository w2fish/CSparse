/* convert CSC form into triplet form */
/* Tim.D. book, ex2.2 */
#include "cs.h"
cs *cs_find (const cs *C)
{
	/* int m, n, nz, p, k, *Tp, *Ti, *w, *Ci, *Cp ; wrong!!! */
	csi m, n, nz, p, k, *Tp, *Ti, *w, *Ci, *Cp ;
	printf("size of csi = %d\n", sizeof(m));
	double *Cx, *Tx ;
	cs *T;
	if (!CS_CSC(C)) return (NULL) ;			/* check input */
	m = C->m ; n = C->n ; Ci = C->i ; Cp = C->p ;
	Cx = C->x ; nz = C->nz ;
	T = cs_spalloc(m, n, Cp[n], Cx != NULL, 1) ;  /* allocate result */
	printf("Cp: %d\t%d\t%d\n", Cp[0], Cp[1], Cp[2]) ;
	printf("C->p: %d\t%d\t%d\n", *(C->p), *(C->p+1), *(C->p+2)) ;
	printf("m = %i\tn = %i\tCp[n] = %i\tnz = %i\n", m, n, Cp[n], nz) ;

	if (!T) return (cs_done (T, NULL, NULL, 0));  /* out of memory */
	printf("nzmax = %i\tnnz = %i\n", T->nzmax, T->nz) ;
	Tp = T->p ; Ti = T->i ; Tx = T->x ;
	for (k = 0 ; k < n ; k++)
	{
		for(p = Cp[k] ; p < Cp[k+1] ; p++)
		{
			Tp[p] = k ;
			Ti[p] = Ci[p] ;
			if(Cx) Tx[p] = Cx[p] ;
			T->nz++ ;
		}
	}
	return T ;
}

/* convert CSC form into triplet form */
#include "cs.h"
cs *cs_find (const cs *C)
{
	int m, n, nz, p, k, *Tp, *Ti, *w, *Ci, *Cp ;
	double *Cx, *Tx ;
	cs *T;
	if (CS_CSC(T)) return (NULL) ;			/* check input */
	m = C->m ; n = C->n ; Ci = C->i ; Cp = C->p ;
	Cx = C->x ; nz = C->nz ;
	T = cs_spalloc(m, n, Cp[n], Cx != NULL, 1) ;  /* allocate result */
	if (!T) return (cs_done (T, NULL, NULL, 0));  /* out of memory */
	Tp = T->p ; Ti = T->i ; Tx = T->x ;
	for (k = 0 ; k < n ; k++)
	{
		for(p = Cp[k] ; p < Cp[k+1] ; p++)
		{
			Tp[p] = k ;
			Ti[p] = Ci[p] ;
			if(Cx) Tx[p] = Cx[p] ;
		}
	}
	return T ;
}

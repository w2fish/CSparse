/* 20150422 */
/* Tim.D. book, ex3.7 */
/* solve Ax=b */
/* A is either upper (lo=0) or lower (lo=1) triangular */
/* rows and cols of A is permuted by unknown matrix P and Q */
#include "cs.h"
csi cs_lusolvep2 (cs *A, double *x, csi lo)
{
	csi j, q, n, k, s, *Ap, *Ai ;
	csi *r = NULL, *z = NULL ; 
	double *Ax, ;
	List L ;
	Position P ;
	if (!CS_CSC (A) || !x) return (-1) ;
	Ap = A->p ; Ai = A->i ; Ax = A->x ; n = A->n ;
	r = cs_calloc(n, sizeof(csi)) ; /* r[i]: count of nonzeros in row i */
	z = cs_calloc(n, sizeof(csi)) ; /* z[i]: ex-or of all col indices 
					 of nonzeros in row i */
	if (!r || !z) return -1 ;
	/* initialize r, z from A */
	for (j=0; j<n; j++)
	{
		for (p=Ap[j]; p<Ap[j+1]; p++)
		{
			i = Ai[p] ; /* row index */
			r[i]++ ;
			z[i] ^= j ;
		}
	}
	/* initialize L from r */
	for (i=0; i<n; i++)
	{
		if (r[i] == 1) Insert(i, L, L) ;
	}
	/* find out permutation vector p, q, 
	 * lo=1:   p: move row i in p[i];        q: move col i in q[i]
	 * lo=0:   p: move row (n-i-1) in p[i];  q: move col (n-i-1) in q[i] */
	L = MakeEmpty(L) ;
	for (k=0; k<n; k++)
	{
		if (IsEmpty(L)) return -1 ; /* A bad */
		P = L->Next ;               /* the 1st node */
		i = P->x ;                  /* row index */
		j = z[i] ;                  /* col index */
		p[k] = i ;                  /* append i to p */
		q[k] = j ;                  /* append j to q */
		for (p=Ap[j]; p<Ap[j+1]; p++)
		{
			z[Ai[p]] ^= j ;     /* remove j from z[t], t is all
					       nonzero row indices  */
			r[Ai[p]]--;         /* decrease row count r[t], t is
					       all nonzero row indices */
		}
		DeleteFirst(L) ;            /* delete P */
		for (s=0; s<n; s++)
		{
			if (r[s] == 1) Insert(s, L, L) ;
		}
	}		
	/* solve Ax=b */


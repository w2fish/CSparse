/* 20150422 */
/* Tim.D. book, ex3.7 */
/* solve Ax=b */
/* A is either upper (lo=0) or lower (lo=1) triangular */
/* rows and cols of A is permuted by unknown matrix P and Q */
#include "cs.h"
csi cs_lusolvep2 (cs *A, double *x, csi lo)
{
	csi j, i, n, k, s, *Ap, *Ai ;
	csi *r = NULL, *z = NULL, *w = NULL ;
        csi *p = NULL, *q = NULL, *pinv = NULL ; 
	double *Ax ;
	List L ;
	Position P ;
	if (!CS_CSC (A) || !x) return (0) ;
	Ap = A->p ; Ai = A->i ; Ax = A->x ; n = A->n ;
	r = cs_calloc(n, sizeof(csi)) ; /* r[i]: count of nonzeros in row i */
	z = cs_calloc(n, sizeof(csi)) ; /* z[i]: ex-or of all col indices 
					 of nonzeros in row i */
	w = cs_malloc(n, sizeof(csi)) ; /* w[i]: diagonal entry index of row i 
					   when lo=1 or row (n-i0) when lo=0 */
	p = cs_malloc(n, sizeof(csi)) ;
	q = cs_malloc(n, sizeof(csi)) ;
	if (!r || !z || !w) return 0 ;
	/* initialize r, z from A */
	for (j=0; j<n; j++)
	{
		for (s=Ap[j]; s<Ap[j+1]; s++)
		{
			i = Ai[s] ; /* row index */
			r[i]++ ;
			z[i] ^= j ;
		}
	}
	/* initialize L from r */
	L = MakeEmpty(L) ;
	for (i=0; i<n; i++)
	{
		if (r[i] == 1) Insert(i, L, L) ;
	}
	/* find out permutation vector p, q, 
	 * lo=1:   p: move row i in p[i];        q: move col i in q[i]
	 * lo=0:   p: move row (n-i0) in p[i];  q: move col (n-i0) in q[i] */
	for (k=0; k<n; k++)
	{
		if (IsEmpty(L)) return 0 ; /* A bad */
		P = L->Next ;               /* the 1st node */
		i = P->x ;                  /* row index */
		j = z[i] ;                  /* col index */
		p[k] = i ;                  /* append i to p */
		q[k] = j ;                  /* append j to q */
		for (s=Ap[j]; s<Ap[j+1]; s++)
		{
			z[Ai[s]] ^= j ;     /* remove j from z[t], t is all
					       nonzero row indices  */
			r[Ai[s]]--;         /* decrease row count r[t], t is
					       all nonzero row indices */
			if (i == Ai[s]) 
			{
				w[k] = s ; /* save diagonal entry index in w */
			}
		}
		DeleteFirst(L) ;            /* delete P */
		for (s=0; s<n; s++)
		{
			if (r[s] == 1) Insert(s, L, L) ;
		}
	}		
	pinv = cs_pinv(p, n) ; /* pinv is inverse of p */
	/* solve Ax=b */
	if (lo == 1)
	{
		for (k=0; k<n; k++)
		{
			j = q[k] ; /* original k col is at q[k] after permutate */
			x[k] /= Ax[w[k]] ;
			for (s=Ap[j]; s<Ap[j+1]; s++)
			{
				if (s != w[k]) /* not diagonal entry */
				{
					/* x[Ai[s]] -= x[j] * Ax[s] ; */
					x[pinv[Ai[s]]] -= x[k] * Ax[s] ;
				}
			}
		}
	}
	else
	{
		for (k=n-1; k>=0; k--)
		{
			j = q[n-k-1] ;
			x[k] /= Ax[w[n-k-1]] ;
			for (s=Ap[j]; s<Ap[j+1]; s++)
			{
				if (s != w[n-k-1])
				{
					x[pinv[n-Ai[s]-1]] -= x[k] * Ax[s] ;
				}
			}
		}
	}
	/* release */
	free(w) ;
	free(r) ;
	free(z) ;
	free(p) ;
	free(q) ;
	free(pinv) ;
	DeleteList(L) ;
	return 1 ;
}

/* 20150404 */
/* Tim.D. book, ex2.17 */
/* dot product of 2 sparse col vectors */
/* more efficient than cs_transpose + cs_multiply */
/* 2 cases: [1] row index unsorted [2] row index sorted */
/* Testing with the same matrix in sorted and unsorted forms shows that
   the former is much faster for both cs_transpose + cs_multiply and cs_dot */
#include "cs.h"
double cs_dot(cs *x, cs *y)
{
	int sorted = 1;
	csi m, p, t, xnz, ynz, nz, *xi, *xp, *yi, *yp ;
	double *xx, *yx ;
	double s = 0 ;
	/* check input */
	if (!x || !y || x->m != y->m)
	{
		printf("input bad, quit\n") ; return 0 ;
	}
	/* remove duplicate entry */
	cs_dupl(x) ;
	cs_dupl(y) ;
	
	/* print x, y */
	/*printf("x = \n") ; cs_print(x, 1) ;
	printf("y = \n") ; cs_print(y, 1) ;*/
	
	/* set variables */
	m = x->m ; 
	xnz = x->nz ; xi = x->i ; xp = x->p ; xx = x->x ;
	ynz = y->nz ; yi = y->i ; yp = y->p ; yx = y->x ;
	/* check if x and y sorted */
	sorted = cs_issorted(x) && cs_issorted(y) ;
	if (sorted)
	{
		printf("x and y is sorted\n") ;
		/* for (p=xp[0],t=yp[0]; p<xp[1],t<yp[1]; ) wrong! */
		/* comma evaluates all operands and yields value of the last one */
		for (p=xp[0],t=yp[0]; p<xp[1] && t<yp[1]; )
		{
			if (xi[p] == yi[t]) 
			{
				s += xx[p++] * yx[t++] ; 
			}
			else if (xi[p] > yi[t])
			{
				t++ ;
			}
			else if (xi[p] < yi[t])
			{
				p++ ;
			}
		}
		printf("my loop done\n") ;
	}
	else
	{
		csi *w = (csi *)malloc(sizeof(csi) * m) ;
		if (!w) 
		{
			printf("allocate w fail, quit\n") ; return 0 ;
		}
		for(p=0; p<m; p++) w[p] = -1 ;
		/* index of w is row index of y */
		/* value of w is -1 when no entry on that row of y */
		/* otherwise, value of w = t, i.e. index of entry */
		for(t=yp[0]; t<yp[1]; t++)
		{
			w[yi[t]] = t ;
		}
		for(p=xp[0]; p<xp[1]; p++)
		{
			/* y has entry at this row */
			if (w[xi[p]] != -1) 
			{
				s += xx[p] * yx[w[xi[p]]] ;
			}
		}
		cs_free(w) ;
	}
	return s ;
}

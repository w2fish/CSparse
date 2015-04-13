/* 20150413 */
/* Tim.D. book, ex2.29 */
/* modify sparse matrix A by adding k empty rows or columns */
#include "cs.h"
#define	COL	0
#define	ROW	1
csi cs_addemp(cs *A, int RowOrCol, csi k, csi start)
{
	if (!CS_CSC(A))
	{
		printf("input bad, quit\n") ; return 0 ;
	}
	csi m, n, j, p, flag ;
	csi *Ap, *Ai ;
	m = A->m ; n = A->n ; Ap = A->p ; Ai = A->i ;
	/* check dimension */
	if ((RowOrCol == COL && start > n) || (RowOrCol == ROW && start > m))
	{
		printf("dimension wrong, quit\n") ; return 0 ;
	}
	if (RowOrCol == ROW)
	{
		if (start < m)
		{
			for (j=0; j<n; j++)
			{
				for (p=Ap[j]; p<Ap[j+1]; p++)
				{
					if (Ai[p] >= start)
					{
						Ai[p] += k ;
					}
				}
			}
		}
		A->m += k ;  /* resize A */
	}
	else if (RowOrCol == COL)
	{
		/* reallocate A->p */
		A->p = cs_realloc(A->p, n+k+1, sizeof(csi), &flag) ;
		if (!flag)
		{
			printf("reallocate A->p fail, quit\n") ; return 0 ;
		}
		Ap = A->p ;  /* A->p has been reallocated */
		/* Ap[j] after k cols */
		/*for (j=start+k; j<n+k+1; j++)*/
		for (j=n+k; j>=start+k; j--)
		{
			Ap[j] = Ap[j-k] ;
		}
		/* Ap[j] inside the k cols */
		/*if (start == 0)
		{
			for (j=start; j<start+k; j++)
			{
				Ap[j] = 0 ;
			}
		}
		else
		{
			for (j=start; j<start+k; j++)
			{
				Ap[j] = Ap[start-1] ;
			}
		}*/
		for (j=start; j<start+k; j++)
		{
			Ap[j+1] = Ap[start] ;
		}
		A->n += k ;
	}	
	return 1 ;
}

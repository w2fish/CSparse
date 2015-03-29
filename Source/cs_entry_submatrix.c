/* 20150330 */
/* add a k-by-k dense matrix x to a triplet matrix T */
csi cs_entry_submatrix(cs *T, int k, int *i, int *j, double **x)
{
	int s = 0, t = 0 ;
	if(!CS_TRIPLET(T) || !T->x || !i || !j) return 0 ; /* check input */
	if(T->nz >= T->nmax && !cs_sprealloc(T, 2*(T->nmax))) return 0 ;
	for(s=0; s<k; s++)
	{
		for(t=0; t<k; t++)
		{
			T->x[T->nz] = x[s][t] ;
			T->i[T->nz] = i[s] ;
			T->p[T->nz++] = j[t] ;
			T->m = CS_MAX(T->m, i[s]+1) ;
			T->n = CS_MAX(T->n, j[t]+1) ;
		}
	}
	return 1 ;
}

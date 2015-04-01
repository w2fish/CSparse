/* the comparison function for qsort */
int compare_double(const void *a, const void *b)
{
	const double *da = (const double *)a ;
	const double *db = (const double *)b ;

	return (*da > *db) - (*da < *db) ;
}

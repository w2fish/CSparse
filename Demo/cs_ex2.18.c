/* 20150404 */
/* calculate x' * y */
/* test cs_dot, compare speed with cs_transpose + cs_multiply */
/* Testing with the same matrix in sorted and unsorted forms shows that
   the former is much faster for both cs_transpose + cs_multiply and cs_dot */
/* command: cs_ex2.17 sortOrNot method */
/* method = 1:  cs_transpose + cs_multiply  
            2:  cs_dot
			3:  cs_transpose + cs_multiply and cs_dot  */
#include "cs.h"
#include <time.h>
int main(int argc, char * argv[])
{
	int sort = atoi(argv[1]) ;
	int method = atoi(argv[2]) ;
	clock_t t ;
	cs *T = NULL, *x = NULL, *y = NULL, *D = NULL, *E = NULL ;
	csi xm, ym ;
	FILE *fp ;
	char fileMatrix1[256] = "fileMatrix1" ;
	char fileMatrix2[256] = "fileMatrix2" ;
	double s1, s2 ;
	/* load x */
	fp = fopen(fileMatrix1, "r") ;
	if (!fp)
	{
		printf("open fileMatrix fail, quit\n") ; return 0 ;
	}
	T = cs_load(fp) ;
	fclose(fp) ;
	if (!T)
	{
		printf("load T fail, quit\n") ; return 0 ;
	}
	x = cs_compress(T) ;
	cs_spfree(T) ;
	/* load y */
	fp = fopen(fileMatrix2, "r") ;
	if (!fp)
	{
		printf("open fileMatrix fail, quit\n") ; return 0 ;
	}
	T = cs_load(fp) ;
	fclose(fp) ;
	if (!T)
	{
		printf("load T fail, quit\n") ; return 0 ;
	}
	y = cs_compress(T) ;
	cs_spfree(T) ;
	/* set equal length */
	xm = x->m ; ym = y->m ;
	if (xm > ym) 
	{
		y->m = xm ;
	}
	else
	{
		x->m = ym ;
	}
	/* sort x, y */
	if (sort)
	{
		x = cs_sort_fast(x) ;
		y = cs_sort_fast(y) ;
	}

	/* print x, y */
	/*printf("x = \n") ; cs_print(x, 1) ;
	printf("y = \n") ; cs_print(y, 1) ;*/

	if (method == 1 || method == 3)
	{
		/* x' * y by transpose and multiply */
		t = clock() ;
		D = cs_transpose(x, 1) ;
		/*printf("x' = \n") ; cs_print(D, 0) ;*/
		E = cs_multiply(D, y) ;
		/*printf("x' * y = \n") ; cs_print(E, 0) ;*/
		s1 = E->x[0] ;
		t = clock() - t ;
		printf("s1 time = %lf s \n", (double)t/CLOCKS_PER_SEC) ;
		printf("s1 = %lf\n", s1) ;
	}
	if (method == 2 || method == 3)
	{
		/* x' * y by direct dot product */
		t = clock() ;
		s2 = cs_dot(x, y) ;
		t = clock() - t ;
		printf("s2 time = %lf s \n", (double)t/CLOCKS_PER_SEC) ;
		printf("s2 = %lf\n", s2) ;
	}

	/* release */
	cs_spfree(x) ;
	cs_spfree(y) ;
	cs_spfree(D) ;
	cs_spfree(E) ;

	return 0 ;
}

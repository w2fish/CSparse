/* 20150424 */
/* test cs_lsolve2 */
/* another version of cs_lsolve, reduce time if b has zero entries */
/* solve Lx=b where x and b are dense.  x=b on input, solution on output. */
/* It turns out time saved by cs_lsolve2 really depends on how many x[j] is
   still ZERO during calculation, varies from
   0%: when the first few b[j] is nonzero to
   100%: when the last few b[j] is nonzero  */
#include "cs.h"
#include <time.h>
#include <stdlib.h>
int main(int argc, char * argv[])
{
	srand(time(NULL)) ;
	int print = atoi(argv[1]) ;
	int bnonzero = atoi(argv[2]) ;
	clock_t time ;
	cs *T = NULL, *L = NULL ;
	char fileMatrix[256] = "fileMatrix" ;
	char fileVectorX[256] = "fileVectorX" ;
	FILE *fp ;
	csi j, n, flag ;
	double *x, *b ;
	/* load L */
	fp = fopen(fileMatrix, "r") ;
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
	L = cs_compress(T) ;
	T = cs_spfree(T) ;
	n = L->n ;
	/* allocate x */
	x = cs_calloc(n, sizeof(double)) ;
	b = cs_calloc(n, sizeof(double)) ;
	if (!x || !b)
	{
		printf("allocate x or b fail, quit\n") ; return 0 ;
	}
	/* load b into x */
	fp = fopen(fileVectorX, "r") ;
	if (!fp)
	{
		printf("open fileVectorX fail, quit\n") ; return 0 ;
	}
/*	for (j=0; j<bnonzero; j++)
	{
		fscanf(fp, "%lf", &b[n-j-1]) ;
	}*/ /* save no time */
/*	for (j=0; j<bnonzero; j++)
	{
		int t = rand() % n ;
		printf("t = %d\n", t) ;
		fscanf(fp, "%lf", &b[t]) ; 
	} */ /* this is something in between */
	for (j=0; j<bnonzero; j++)
	{
		fscanf(fp, "%lf", &b[n-j-1]) ; /* save the most time */
	}
	fclose(fp) ;
	for (j=0; j<n; j++)
	{
		x[j] = b[j] ;
	}
	if (print)
	{
		printf("b = \n") ;
		for(j=0; j<n; j++)
		{
			printf("%lf\t", x[j]) ;
		}
		printf("\n") ;
		printf("L = \n") ; cs_print(L, 0) ;
	}
	/* solve L * x = b */
	time = clock() ;
	flag = cs_lsolve2(L, x) ;
	time = clock() - time ;
	printf("cs_lsolve2 time = %lfs\n", (double)time/CLOCKS_PER_SEC) ;
	if (!flag)
	{
		printf("cs_lsolve2 fail, quit\n") ;
		L = cs_spfree(L) ;
		x = cs_free(x) ;
		return 0 ;
	}
	/* print */
	if (print)
	{
		printf("x = \n") ;
		for(j=0; j<n; j++)
		{
			printf("%lf\t", x[j]) ;
		}
		printf("\n") ;
	}
	/**** solve L * x = b by cs_solve to compare time ****/
	/* load b into x */
	for (j=0; j<n; j++)
	{
		x[j] = b[j] ;
	}
	time = clock() ;
	flag = cs_lsolve(L, x) ;
	time = clock() - time ;
	printf("cs_lsolve time = %lfs\n", (double)time/CLOCKS_PER_SEC) ;
	if (!flag)
	{
		printf("cs_lsolve fail, quit\n") ;
		L = cs_spfree(L) ;
		x = cs_free(x) ;
		return 0 ;
	}
	/* print */
	if (print)
	{
		printf("x = \n") ;
		for(j=0; j<n; j++)
		{
			printf("%lf\t", x[j]) ;
		}
		printf("\n") ;
	}
	/* releas */
	L = cs_spfree(L) ;
	x = cs_free(x) ;
	b = cs_free(b) ;

	return 0 ;
}


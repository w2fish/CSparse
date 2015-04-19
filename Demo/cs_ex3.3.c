/* 20150418 */
/* test cs_lsolverp */
/* solve Lx=b where x and b are dense.  x=b on input, solution on output. */
/* another version of cs_lsovle that rows of L is permuted */
#include "cs.h"
int main(int argc, char * argv[])
{
	int print = atoi(argv[1]) ;
	cs *T = NULL, *L = NULL ;
	char fileMatrix[256] = "fileMatrix" ;
	char fileVectorX[256] = "fileVectorX" ;
	FILE *fp ;
	csi j, n, flag ;
	double *x ;
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
	x = cs_malloc(n, sizeof(double)) ;
	if (!x)
	{
		printf("allocate x fail, quit\n") ; return 0 ;
	}
	/* load b into x */
	fp = fopen(fileVectorX, "r") ;
	if (!fp)
	{
		printf("open fileVectorX fail, quit\n") ; return 0 ;
	}
	for (j=0; j<n; j++)
	{
		fscanf(fp, "%lf", &x[j]) ;
	}
	fclose(fp) ;
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
	flag = cs_lsolverp(L, x) ;
	if (!flag)
	{
		printf("cs_lsolverp fail, quit\n") ;
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

	return 0 ;
}

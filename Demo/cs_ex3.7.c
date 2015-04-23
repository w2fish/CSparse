/* 20150423 */
/* test cs_lusolve2 */
/* solve Ax=b */
/* A is either upper (lo=0) or lower (lo=1) triangular */
/* rows and cols of A is permuted by unknown matrix P and Q */
#include "cs.h"
int main(int argc, char * argv[])
{
	int print = atoi(argv[1]) ;
	csi lo = (csi)atoi(argv[2]) ;
	cs *T = NULL, *A = NULL ;
	char fileMatrix[256] = "fileMatrix" ;
	char fileVectorX[256] = "fileVectorX" ;
	FILE *fp ;
	csi j, n, flag ;
	double *x ;
	/* load A */
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
	A = cs_compress(T) ;
	T = cs_spfree(T) ;
	n = A->n ;
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
		printf("A = \n") ; cs_print(A, 0) ;
	}
	/* solve A * x = b */
	flag = cs_lusolvep2(A, x, lo) ;
	if (!flag)
	{
		printf("cs_lusolvep2 fail, quit\n") ;
		A = cs_spfree(A) ;
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
	A = cs_spfree(A) ;
	x = cs_free(x) ;

	return 0 ;
}

/* 20150407 */
/* test cs_subm */
/* cs version of matlab statement C = A(i, j) */
/* where i, j are integer vectors */
/* i, j may OR may not contain duplicate indices */
#include "cs.h"
int main(int argc, char * argv[])
{
	int print = atoi(argv[1]) ;
	int il = atoi(argv[2]) ;
	int jl = atoi(argv[3]) ;
	cs *T = NULL, *A = NULL, *C = NULL ;
	csi i ;
	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
	char fileVectorX[256] = "fileVectorX" ;
	char fileVectorY[256] = "fileVectorY" ;
	/* allocate x, y */
	int *x = (int *)malloc(sizeof(int) * il) ;
	int *y = (int *)malloc(sizeof(int) * jl) ;
	/* read x from file */
	fp = fopen(fileVectorX, "r") ;
	for(i=0; i<il; i++)
	{
		fscanf(fp, "%d", &(x[i])) ;
	}
	/* read y from file */
	fp = fopen(fileVectorY, "r") ;
	for(i=0; i<jl; i++)
	{
		fscanf(fp, "%d", &(y[i])) ;
	}
	/* load A */
	fp = fopen(fileMatrix, "r") ;
	if (!fp)
	{
		printf("open fileMatrix fail, quit\n") ; return 0 ;
	}
	T = cs_load(fp) ;
	printf("T = \n") ; cs_print(T, 1) ;
	fclose(fp) ;
	if (!T)
	{
		printf("load T fail, quit\n") ; return 0 ;
	}
	A = cs_compress(T) ;
	T = cs_spfree(T) ;
	/* print x */
	printf("x = \n") ;
	for(i=0; i<il; i++)
	{
		printf("%d\n", x[i]) ;
	}
	/* print y */
	printf("y = \n") ;
	for(i=0; i<jl; i++)
	{
		printf("%d\n", y[i]) ;
	}
	/* calculate C */
	C = cs_subm2(A, x, il, y, jl) ;
	if (!C) 
	{
		printf("cs_subm2 fail, quit\n") ; return 0 ;
	}
	/* print */
	if (print)
	{
		printf("A = \n") ; cs_print(A, 0) ;
		printf("C = \n") ; cs_print(C, 0) ;
	}
	/* release */
	printf("release...\n") ;
	A = cs_spfree(A) ;
	free(x) ;
	free(y) ;
	printf("release done.\n") ;
	
	return 0 ;
}

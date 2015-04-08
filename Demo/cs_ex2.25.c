/* 20150408 */
/* test cs_subm3 */
/* cs version of matlab statement A(i, j) = C */
/* where i, j are integer vectors */
/* i, j may or may not contain duplicate indices */
/* command: cs_ex2.25 printOrNot ilength jlength */
#include "cs.h"
int main(int argc, char * argv[])
{
	int print = atoi(argv[1]) ;
	int il = atoi(argv[2]) ;
	int jl = atoi(argv[3]) ;
	cs *T = NULL, *A = NULL, *C = NULL, *D = NULL ;
	csi i ;
	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
	char fileMatrix1[256] = "fileMatrix1" ;
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
	/* load C */
	fp = fopen(fileMatrix1, "r") ;
	if (!fp)
	{
		printf("open fileMatrix1 fail, quit\n") ; return 0 ;
	}
	T = cs_load(fp) ;
	printf("T = \n") ; cs_print(T, 1) ;
	fclose(fp) ;
	if (!T)
	{
		printf("load T fail, quit\n") ; return 0 ;
	}
	C = cs_compress(T) ;
	T = cs_spfree(T) ;
	
	/* print */
	if (print)
	{
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
		printf("A = \n") ; cs_print(A, 0) ;
		printf("C = \n") ; cs_print(C, 0) ;
	}
	/* calculate C */
	D = cs_subm3(A, C, x, il, y, jl) ;
	if (!D) 
	{
		printf("cs_subm3 fail, quit\n") ; return 0 ;
	}
	/* print */
	if (print)
	{
		printf("D = \n") ; cs_print(D, 0) ;
	}
	/* release */
	printf("release...\n") ;
	A = cs_spfree(A) ;
	C = cs_spfree(C) ;
	D = cs_spfree(D) ;
	free(x) ;
	free(y) ;
	printf("release done.\n") ;
	
	return 0 ;
}


/* 20150410 */
/* test cs_permtranspose */
/* cs version of matlab statement C = A(p,q)' */
/* p, q are permutation vectors */
#include "cs.h"
int main(int argc, char * argv[])
{
	int print = atoi(argv[1]) ;
	cs *T = NULL, *A = NULL, *C = NULL ;
	csi i ;
	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
	char fileVectorX[256] = "fileVectorX" ;
	char fileVectorY[256] = "fileVectorY" ;
	csi *pinv = NULL, *qinv = NULL ;
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
	/* allocate p, q, pinv, qinv */
	csi *p = (csi *)malloc(sizeof(csi) * A->m) ;
	csi *q = (csi *)malloc(sizeof(csi) * A->n) ;
	/* read p from file */
	fp = fopen(fileVectorX, "r") ;
	for(i=0; i<A->m; i++)
	{
		fscanf(fp, "%d", &(p[i])) ;
	}
	/* read q from file */
	fp = fopen(fileVectorY, "r") ;
	for(i=0; i<A->n; i++)
	{
		fscanf(fp, "%d", &(q[i])) ;
	}
	/* calculate pinv, qinv */
	pinv = cs_pinv(p, A->m) ;
	qinv = cs_pinv(q, A->n) ;
	/* print */
	if (print)
	{
		/* print p */
		printf("p = \n") ;
		for(i=0; i<A->m; i++)
		{
			printf("%d\n", p[i]) ;
		}
		/* print pinv */
		printf("pinv = \n") ;
		for(i=0; i<A->m; i++)
		{
			printf("%d\n", pinv[i]) ;
		}
		/* print q */
		printf("q = \n") ;
		for(i=0; i<A->n; i++)
		{
			printf("%d\n", q[i]) ;
		}
		/* print qinv */
		printf("qinv = \n") ;
		for(i=0; i<A->n; i++)
		{
			printf("%d\n", qinv[i]) ;
		}
		printf("A = \n") ; cs_print(A, 0) ;
	}
	/* calculate C = A(p,q)' */
	C = cs_permtranspose(A, pinv, qinv, 1) ;
	if (!C) 
	{
		printf("cs_permtranspose fail, quit\n") ; return 0 ;
	}
	/* print */
	if (print)
	{
		printf("C = \n") ; cs_print(C, 0) ;
	}
	/* release */
	printf("release...\n") ;
	A = cs_spfree(A) ;
	C = cs_spfree(C) ;
	p = cs_free(p) ;
	q = cs_free(q) ;
	pinv = cs_free(pinv) ;
	qinv = cs_free(qinv) ;
	printf("release done.\n") ;
	
	return 0 ;
}

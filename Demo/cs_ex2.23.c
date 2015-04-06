/* 20150406 */
/* test cs_subm */
/* cs version of matlab statement C = A(i1:i2, j1:j2) */
#include "cs.h"
int main(int argc, char * argv[])
{
	int print = atoi(argv[1]) ;
	csi i1 = (csi)atoi(argv[2]) ;
	csi i2 = (csi)atoi(argv[3]) ;
	csi j1 = (csi)atoi(argv[4]) ;
	csi j2 = (csi)atoi(argv[5]) ;
	cs *T = NULL, *A = NULL, *C = NULL ;
	csi am, an, m, n ;
	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
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
	am = A->m ; an = A->n ;
	/* print */
	if (print)
	{
		printf("A = \n") ; cs_print(A, 1) ;
	}
	/* calculate cs_subm */
	C = cs_subm(A, i1, i2, j1, j2) ;
	/* print */
	if (print)
	{
		printf("C = \n") ; cs_print(C, 0) ;
	}
	/* release */
	A = cs_spfree(A) ;
	C = cs_spfree(C) ;

	return 0 ;
}


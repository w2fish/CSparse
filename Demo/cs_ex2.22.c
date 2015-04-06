/* 20150406 */
/* test cs_hcat, cs_vcat */
/* command: cs_ex2.22 print method */
/* method = 1: cs_hcat */
/*          2: cs_vcat */
#include "cs.h"
int main(int argc, char * argv[])
{
	int print = atoi(argv[1]) ;
	int method = atoi(argv[2]) ;
	cs *T = NULL, *A = NULL, *B = NULL, *C = NULL, *D = NULL ;
	csi am, an, bm, bn, m, n ;
	FILE *fp ;
	char fileMatrix1[256] = "fileMatrix1" ;
	char fileMatrix2[256] = "fileMatrix2" ;
	/* load A */
	fp = fopen(fileMatrix1, "r") ;
	if (!fp)
	{
		printf("open fileMatrix fail, quit\n") ; return 0 ;
	}
	T = cs_load(fp) ;
	printf("T(A) = \n") ; cs_print(T, 1) ;
	fclose(fp) ;
	if (!T)
	{
		printf("load T fail, quit\n") ; return 0 ;
	}
	A = cs_compress(T) ;
	T = cs_spfree(T) ;
	am = A->m ; an = A->n ;
	/* load B */
	fp = fopen(fileMatrix2, "r") ;
	if (!fp)
	{
		printf("open fileMatrix fail, quit\n") ; return 0 ;
	}
	T = cs_load(fp) ;
	printf("T(B) = \n") ; cs_print(T, 1) ;
	fclose(fp) ;
	if (!T)
	{
		printf("load T fail, quit\n") ; return 0 ;
	}
	B = cs_compress(T) ;
	T = cs_spfree(T) ;
	bm = B->m ; bn = B->n ;
	/* print */
	if (print)
	{
		printf("A = \n") ; cs_print(A, 1) ;
		printf("B = \n") ; cs_print(B, 1) ;
	}
	/* calculate cs_hcat or cs_vcat */
	if (method == 1)
	{
		C = cs_hcat(A, B) ;
		if (!C)
		{
			printf("cs_hcat fail, quit\n") ; return 0 ;
		}
	}
	if (method == 2)
	{
		D = cs_vcat(A, B) ;
		if (!D)
		{
			printf("cs_vcat fail, quit\n") ; return 0 ;
		}
	}
	/* print */
	if (print)
	{
		if (method == 1) 
		{
			printf("C = \n") ; cs_print(C, 0) ;
		}
		if (method == 2)
		{
			printf("D = \n") ; cs_print(D, 0) ;
		}
	}
	/* release */
	A = cs_spfree(A) ;
	B = cs_spfree(B) ;
	C = cs_spfree(C) ;
	D = cs_spfree(D) ;

	return 0 ;
}

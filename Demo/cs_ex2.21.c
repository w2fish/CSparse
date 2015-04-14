/* 20150405 */
/* test cs_saxpy, compare to cs_add */
/* command: cs_ex2.21 print nodupl loop */
/* test result: set loop = 5e7, time for (1 allocation + 1 release) */
/* is 46.9 ns */
#include "cs.h"
#include <time.h>
int main(int argc, char * argv[])
{
	int print = atoi(argv[1]) ;
	int nodupl = atoi(argv[2]) ;
	int loop = atoi(argv[3]) ;
	clock_t t ;
	cs *T = NULL, *A = NULL, *B = NULL, *C = NULL, *D = NULL, *As = NULL ;
	csi am, an, bm, bn, m ;
	FILE *fp ;
	char fileMatrix1[256] = "fileMatrix1" ;
	char fileMatrix2[256] = "fileMatrix2" ;
	csi *w = NULL ;
	double *x = NULL ;
	int i ;
	/* load A */
	fp = fopen(fileMatrix1, "r") ;
	if (!fp)
	{
		printf("open fileMatrix fail, quit\n") ; return 0 ;
	}
	T = cs_load(fp) ;
	/*printf("T(A) = \n") ; cs_print(T, 1) ;*/
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
	/*printf("T(B) = \n") ; cs_print(T, 1) ;*/
	fclose(fp) ;
	if (!T)
	{
		printf("load T fail, quit\n") ; return 0 ;
	}
	B = cs_compress(T) ;
	T = cs_spfree(T) ;
	bm = B->m ; bn = B->n ;
	/* check input */
	if (am != bm)
	{
		/*printf("am = %d\n", (int)am) ;
		printf("bm = %d\n", (int)bm) ;*/
		m = CS_MAX(am, bm) ;
		A->m = B->m = m ;
	}
	/* remove duplicate from A, B */
	if (nodupl)
	{
		cs_dupl(A) ;
		cs_dupl(B) ;
		A->m = am ; A->n = an;
		B->m = bm ; B->n = bn ;
	}
	/* allocate w, x */
	w = cs_calloc(am, sizeof(csi)) ;
	x = cs_malloc(am, sizeof(double)) ;
	if (!w || !x)
	{
		printf("allocate w or x fail, quit\n") ; return 0 ;
	}
	/* print */
	if (print)
	{
		printf("A = \n") ; cs_print(A, 1) ;
		printf("B = \n") ; cs_print(B, 1) ;
	}
	/* C  = A + B by cs_add */
	t = clock() ;
	for (i=0; i<loop; i++)
	{
		C = cs_add(A, B, 1, 1) ;
		if (!C)
		{
			printf("cs_add fail, quit\n") ; return 0 ;
		}
		if (i < loop-1) C = cs_spfree(C) ;
	}
	t = clock() - t ;
	printf("cs_add time = %lf s \n", (double)t/CLOCKS_PER_SEC) ;
	/* D  = A + B by cs_saxpy */
	t = clock() ;
	for (i=0; i<loop; i++)
	{
		D = cs_saxpy(A, B, 1, 1, w, x) ;
		if (!D)
		{
			printf("cs_saxpy fail, quit\n") ; return 0 ;
		}
		if (i < loop-1) D = cs_spfree(D) ;
	}
	t = clock() - t ;
	printf("cs_saxpy time = %lf s \n", (double)t/CLOCKS_PER_SEC) ;
	/* print */
	if (print)
	{
		printf("C = \n") ; cs_print(C, 1) ;
		printf("D = \n") ; cs_print(D, 1) ;
	}
	/* release */
	printf("release...\n") ;
	A = cs_spfree(A) ;
	B = cs_spfree(B) ;
	C = cs_spfree(C) ;
	D = cs_spfree(D) ;
	w = cs_free(w) ;
	x = cs_free(x) ;
	printf("release done\n") ;

	return 0 ;
}

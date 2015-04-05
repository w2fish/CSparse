/* 20150405 */
/* test cs_multiply3 */ 
/* compare with cs_multiply */
/* command: cs_ex2.20 print nodupl */
/* it turns out much slower than cs_multiply */
#include "cs.h"
#include <time.h>
int main(int argc, char * argv[])
{
	int print = atoi(argv[1]) ;
	int nodupl = atoi(argv[2]) ;
	clock_t t ;
	cs *T = NULL, *A = NULL, *B = NULL, *C = NULL, *D = NULL ;
	csi am, an, bm, bn ;
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
	fclose(fp) ;
	if (!T)
	{
		printf("load T fail, quit\n") ; return 0 ;
	}
	A = cs_compress(T) ;
	cs_spfree(T) ;
	am = A->m ; an = A->n ;
	/* load B */
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
	B = cs_compress(T) ;
	cs_spfree(T) ;
	bm = B->m ; bn = B->n ;
	/* remove duplicate from A, B */
	if (nodupl)
	{
		cs_dupl(A) ;
		cs_dupl(B) ;
		A->m = am ; A->n = an;
		B->m = bm ; B->n = bn ;
	}
	/* print */
	if (print)
	{
		printf("A = \n") ; cs_print(A, 1) ;
		printf("B = \n") ; cs_print(B, 1) ;
	}
	/* C  = A * B by cs_multiply */
	t = clock() ;
	C = cs_multiply(A, B) ;
	if (!C)
	{
		printf("cs_multiply fail, quit\n") ; return 0 ;
	}
	t = clock() - t ;
	printf("cs_multiply time = %lf s \n", (double)t/CLOCKS_PER_SEC) ;
	/* D  = A * B by cs_multiply3 */
	t = clock() ;
	D = cs_multiply3(A, B) ;
	if (!D)
	{
		printf("cs_multiply3 fail, quit\n") ; return 0 ;
	}
	t = clock() - t ;
	printf("cs_multiply3 time = %lf s \n", (double)t/CLOCKS_PER_SEC) ;
	/* print */
	if (print)
	{
		printf("C = \n") ; cs_print(C, 1) ;
		printf("D = \n") ; cs_print(D, 1) ;
	}
	/* release */
	cs_spfree(A) ;
	cs_spfree(B) ;
	cs_spfree(C) ;
	cs_spfree(D) ;

	return 0 ;
}


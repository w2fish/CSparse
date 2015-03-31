/* 20150401 */
/* test cs_sort_slow */
#include "cs.h"
int main()
{
	cs *T, *A ;
	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
	/* read A from file */
	fp = fopen(fileMatrix, "r") ;
	T = cs_load(fp) ; /* load triplet matrix T from stdin */
	fclose(fp);
	printf("T = \n") ; cs_print(T, 0) ;
	A = cs_compress(T) ; /* A = CSC form of T */
	printf("A = \n") ; cs_print(A, 0) ;
	/* sort A */
	A = cs_sort_slow(A) ;
	printf("qsort-sorted A = \n") ; cs_print(A, 0) ;
	/* release */
	cs_spfree(T) ;
	cs_spfree(A) ;

	return 0 ;
}

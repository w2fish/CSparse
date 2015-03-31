/* 20150331 */
/* test cs_sort */
#include "cs.h"
int main()
{
	cs *T, *A, *As ;
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
	As = cs_sort(A) ;
	printf("sorted A = \n") ; cs_print(As, 0) ;
	/* release */
	cs_spfree(A) ;
	cs_spfree(As) ;

	return 0 ;
}

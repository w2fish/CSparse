/* test cs_find.c, convert CSC into triplet */
#include "cs.h"
int main()
{
	cs *T, *A ;
	int m = 3, n = 2 ;
	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
	/* read T from file */
	fp = fopen(fileMatrix, "r") ;
	T = cs_load(fp) ;
	printf("T0 = \n") ; cs_print(T, 0) ;
	fclose(fp) ;
	/* A = CSC form of T */
	A = cs_compress(T) ;
	printf("A = \n") ; cs_print(A, 0) ;
	printf("Ap: %d\t%d\t%d\n", *(A->p), *(A->p+1), *(A->p+2)) ;
	/* T = triplet form of A */
	T = cs_find(A) ;
	printf("T = \n") ; cs_print(T, 0) ;
	/* release */
	cs_spfree(A) ;
	cs_spfree(T) ;

	return 0 ;
}

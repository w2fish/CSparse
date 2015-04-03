/* 20150403 */
/* test cs_copy */
#include "cs.h"
#include <time.h>
int main(int argc, char * argv[])
{
	clock_t t ;
	int print = atoi(argv[1]) ;
	cs *T = NULL, *A = NULL, *C = NULL ;
	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
	
	/* read T from file */
	fp = fopen(fileMatrix, "r") ;
	if (!fp)
	{
		printf("open fileMatrix fail, quit\n") ; return 0 ;
	}
	T = cs_load(fp) ; /* load triplet matrix T from stdin */
	fclose(fp);
	if (!T) 
	{
		printf("load T fail, quit\n") ;
		return 1 ;
	}
	/*printf("T = \n") ; cs_print(T, 0) ; */

	/* compress T into A */
	A = cs_compress(T) ; /* A = CSC form of T */

	/* copy A to C */
	t = clock() ;
	C = cs_copy(A) ;
	t = clock() - t ;
	printf("copy time = %lf s \n", (double)t/CLOCKS_PER_SEC) ;
	if (!C)
	{
		printf("copy A to C fail, quit\n") ; return 0 ;
	}

	/* print */
	if (print)
	{
		printf("A = \n") ; cs_print(A, 0) ;
		printf("C = \n") ; cs_print(C, 0) ;
	}

	/* release */
	cs_spfree(A) ;
	cs_spfree(T) ;
	cs_spfree(C) ;

	return 0 ;
}

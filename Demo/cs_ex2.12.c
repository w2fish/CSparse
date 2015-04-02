/* 20150403 */
/* test cs_ok */
#include "cs.h"
int main(int argc, char * argv[])
{
	cs *T = NULL, *A = NULL, *As = NULL ;
	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
	int flag = 0 ;
	int sorted, values, print ;
	sorted = atoi(argv[1]) ;
	values = atoi(argv[2]) ;
	print = atoi(argv[3]) ;
	
	/* read T from file */
	fp = fopen(fileMatrix, "r") ;
	if(!fp)
	{
		printf("open fileMatrix fail, quit\n") ; return 0 ;
	}
	T = cs_load(fp) ; /* load triplet matrix T from stdin */
	fclose(fp);
	if(!T) 
	{
		printf("load T fail, quit\n") ;
		return 1 ;
	}
	/*printf("T = \n") ; cs_print(T, 0) ; */

	/* compress T into A */
	A = cs_compress(T) ; /* A = CSC form of T */
	/*printf("A = \n") ; cs_print(A, 0) ;*/

	/* sort A */
	A = cs_sort_fast(A) ;
	
	/* drop zeros in A */
	flag = cs_dropzeros(A) ;	

	/* check if A is valid */
	flag = cs_ok(A, sorted, values, print) ;
	if (flag) printf("A ok\n") ;
	else printf("A bad\n") ;

	/* release */
	cs_spfree(T) ;
	cs_spfree(A) ;

	return 0 ;
}

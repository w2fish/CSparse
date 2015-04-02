/* 20150402 */
/* test cs_sort2 */
/* command: *.exe printOrNot */
#include "cs.h"
#include <time.h>
int main(int argc, char * argv[])
{
	int print = atoi(argv[1]);
	clock_t time ;
	csi flag ;
	cs *T = NULL, *A = NULL, *As = NULL ;
	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
	
	/* read A from file */
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

	/* compress T into A and remove duplicate */
	A = cs_compress(T) ; /* A = CSC form of T */
	flag = cs_dupl(A) ; /* remove duplicate element */
	/*printf("A = \n") ; cs_print(A, 0) ;*/

	/* sort A */
	time = clock() ;
	As = cs_sort2(A) ;
	if(!As) 
	{ 
		printf("cs_sort2 bad, quit\n") ; return 0 ; 
	}
	time = clock() - time ;

	/* print result */
	printf("sort2 time = %lf s\n", (double)time/CLOCKS_PER_SEC) ;
	if(print)
	{
		printf("sorted A = \n") ; cs_print(As, 0) ;
	}

	/* release */
	cs_spfree(A) ;
	cs_spfree(As) ;
	cs_spfree(T) ;

	return 0 ;
}

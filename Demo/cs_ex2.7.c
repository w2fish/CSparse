/* 20150331 */
/* test cs_sort */
/* command: *.exe printOrNot */
#include "cs.h"
#include <time.h>
int main(int argc, char * argv[])
{
	int print = atoi(argv[1]);
	clock_t time ;
	csi flag ;
	cs *T, *A, *As ;
	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
	
	/* read A from file */
	fp = fopen(fileMatrix, "r") ;
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
	As = cs_sort(A) ;
	time = clock() - time ;

	/* print result */
	printf("sort time = %lf s\n", (double)time/CLOCKS_PER_SEC) ;
	if(print)
	{
		printf("sorted A = \n") ; cs_print(As, 0) ;
	}

	/* release */
	cs_spfree(A) ;
	cs_spfree(As) ;

	return 0 ;
}

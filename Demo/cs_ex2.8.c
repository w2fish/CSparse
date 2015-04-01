/* 20150401 */
/* test cs_sort_slow */
/* command: *.exe fastOrNot printOrNot */
#include "cs.h"
#include <time.h>
int main(int argc, char * argv[])
{
	int print = atoi(argv[2]) ;
	int fast = atoi(argv[1]) ;
	csi flag ;
	clock_t time ;
	cs *T = NULL, *A = NULL, *As=NULL ;
	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
	/* read A from file */
	fp = fopen(fileMatrix, "r") ;
	T = cs_load(fp) ; /* load triplet matrix T from stdin */
	fclose(fp);
	/*printf("T = \n") ; cs_print(T, 0) ;*/
	A = cs_compress(T) ; /* A = CSC form of T */
	flag = cs_dupl(A) ; /* remove duplicate element */
	/*printf("A = \n") ; cs_print(A, 0) ;*/
	/* sort A */
	time = clock() ;
	if(fast)
	{
		A = cs_sort_fast(A) ; 
	}
	else
	{
		As = cs_sort_slow(A) ;
	}
	time = clock() - time ;
	printf("sort time = %lf s\n", (double)time/CLOCKS_PER_SEC) ;
	if(print)
	{
		if(fast)
		{
			printf("qsort-sorted A = \n") ; cs_print(A, 0) ;
		}
		else
		{
			printf("qsort-sorted A = \n") ; cs_print(As, 0) ;
		}
	}

	/* release */
	cs_spfree(T) ;
	cs_spfree(A) ;
	cs_spfree(As) ;

	return 0 ;
}

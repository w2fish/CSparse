/* 20150413 */
/* test cs_addemp */
/* modify sparse matrix A by adding k empty rows or columns */
/* command: cs_ex2.29 print RowOrCol k start */
#include "cs.h"
int main(int argc, char * argv[])
{
	int print = atoi(argv[1]) ;
	int RowOrCol = atoi(argv[2]) ;
	csi k = atoi(argv[3]) ;
	csi start = (csi)atoi(argv[4]) ;
	cs *T = NULL, *A = NULL ;
	csi flag ;
	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
	/* load A */
	fp = fopen(fileMatrix, "r") ;
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
	if (print)
	{
		printf("T = \n") ; cs_print(T, 1) ;
		printf("A = \n") ; cs_print(A, 1) ;
	}
	T = cs_spfree(T) ;
	/* add k empty columns or rows to position start */
	flag = cs_addemp(A, RowOrCol, k, start) ;
	if (!flag) 
	{
		printf("cs_addemp fail, quit\n") ;
		A = cs_spfree(A) ;
		return 0 ;
	}
	/* print */
	if (print)
	{
		printf("A = \n") ; cs_print(A, 1) ;
	}
	/* release */
	A = cs_spfree(A) ;

	return 0 ;
}	

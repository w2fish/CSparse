/* 20150402 */
/* test cs_compress2 */
#include "cs.h"
int main(int argc, char * argv[])
{
	cs *T = NULL, *A = NULL ;
	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
	
	/* read T from file */
	fp = fopen(fileMatrix, "r") ;
	T = cs_load(fp) ; /* load triplet matrix T from stdin */
	fclose(fp);
	if(!T) 
	{
		printf("load T fail, quit\n") ;
		return 1 ;
	}
	printf("T = \n") ; cs_print(T, 0) ;

	/* create CSC from T , sorted, no duplicate, no numerically zero entry */
	A = cs_compress2(T) ;
	printf("A = \n") ; cs_print(A, 0) ;

	/* release */
	cs_spfree(T) ;
	cs_spfree(A) ;
}

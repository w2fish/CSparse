/* 20150403 */
/* test cs_band */
#include "cs.h"
int main(int argc, char * argv [])
{
	int k1 = atoi(argv[1]) ;
	int k2 = atoi(argv[2]) ;
	cs *T = NULL, *A = NULL ;
	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
	csi flag ;
	
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
	printf("A = \n") ; cs_print(A, 0) ;

	/* remove entry outside band k1 to k2 */
	flag = cs_band(A, (csi)k1, (csi)k2) ;
	if (flag < 0)
	{
		printf("cs_band fail, quit\n") ; return 0 ;
	}
	printf("band A = \n") ; cs_print(A, 0) ;

	/* release */
	cs_spfree(A) ;
	cs_spfree(T) ;

	return 0 ;
}

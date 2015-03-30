/* 20150331 */
/* test cs_expand.c */
#include "cs.h"
int main()
{
	cs *T, *A ;
	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
	/* read T from file */
	fp = fopen(fileMatrix, "r") ;
	T = cs_load(fp) ; /* load triplet matrix T from stdin */
	fclose(fp);
	printf("T = \n") ; cs_print(T, 0) ;
	/* compress T into A */
	A = cs_compress(T) ;
	/* expand A back to T, free T first */
	cs_spfree(T) ;
	T = cs_expand(A) ;
	printf("new T = \n") ; cs_print(T, 0) ;
	/* release */
	cs_spfree(T) ;
	cs_spfree(A) ;
	
	return 0 ;
}

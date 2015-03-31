/* 20150331 */
/* test cs_transpose_triplet */
#include "cs.h"
int main()
{
	cs *T, *Ttr ;
	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
	/* read T from fileMatrix */
	fp = fopen(fileMatrix, "r") ;
	T = cs_load(fp) ;
	printf("T = \n") ; cs_print(T, 0) ;
	/* Ttr = T' */
	Ttr = cs_transpose_triplet(T, 1) ;
	printf("T' = \n") ; cs_print(Ttr, 0) ;

	return 0 ;
}
	

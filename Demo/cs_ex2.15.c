/* 20150403 */
/* test cs_band */
#include "cs.h"
int main(int argc, char * argv [])
{
	cs *T = NULL, *A = NULL ;
	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
	int flag ;
	
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
}

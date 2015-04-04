/* 20150404 */
/* test cs_spcolm */
#include "cs.h"
int main(int argc, char * argv[])
{
	cs *A = NULL ;
	double *D = NULL ;
	csi m, n, i, j ;
	m = (csi)atoi(argv[1]) ;
	n = (csi)atoi(argv[2]) ;
	csi N = m * n ;
	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
	/* allocate D */
	D = (double *)malloc(sizeof(double) * N) ;
	if (!D)
	{
		printf("allocate D fail, quit\n") ; return 0 ;
	}
	/* load D */
	fp = fopen(fileMatrix, "r") ;
	if (!fp)
	{
		printf("open fileMatrix fail, quit\n") ; return 0 ;
	}
	for(j=0; j<N; j++)
	{
		fscanf(fp, "%lf", &D[j]) ;
	}
	/* copy D to A */
	A = cs_spcolm(D, m, n) ;
	if (!A)
	{
		printf("copy D to A fail, quit\n") ; return 0 ;
	}
	printf("A = \n") ; cs_print(A, 0) ;
	/* release */
	cs_free(D) ;
	cs_spfree(A) ;

	return 0 ;
}

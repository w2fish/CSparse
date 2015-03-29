/* 20150330 */
/* test cs_scale.c */
#include "cs.h"
int main()
{
	cs *A, *T ;
	int i = 0 ;
	csi m = 2, n = 3 ;
	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
	char fileVectorX[256] = "fileVectorX" ;
	char fileVectorY[256] = "fileVectorY" ;
	/* allocate x, y */
	double *x = (double *)malloc(sizeof(double) * m) ;
	double *y = (double *)malloc(sizeof(double) * n) ;
	/* read A from file */
	fp = fopen(fileMatrix, "r") ;
	T = cs_load(fp) ; /* load triplet matrix T from stdin */
	fclose(fp);
	printf("T = \n") ; cs_print(T, 0) ;
	A = cs_compress(T) ; /* A = CSC form of T */
	printf("A = \n") ; cs_print(A, 0) ;
	/* read x from file */
	fp = fopen(fileVectorX, "r") ;
	for(i=0; i<m; i++)
	{
		fscanf(fp, "%lf", &(x[i])) ;
	}
	/* read y from file */
	fp = fopen(fileVectorY, "r") ;
	for(i=0; i<n; i++)
	{
		fscanf(fp, "%lf", &(y[i])) ;
	}
	/* print x */
	printf("x = \n") ;
	for(i=0; i<m; i++)
	{
		printf("%lf\n", x[i]) ;
	}
	/* print y */
	printf("y = \n") ;
	for(i=0; i<n; i++)
	{
		printf("%lf\n", y[i]) ;
	}
	/* calculat A = XAY, where X and Y is diagonal */
	cs_scale(A, x, y) ;
	/* print XAY */
	printf("XAY = \n") ; cs_print(A, 0) ;
	/* release */
	printf("release...\n") ;
	cs_spfree(A) ;
	free(x) ;
	free(y) ;
	printf("release done.\n") ;

	return 0 ;
}

/* test cs_gatxpy.c, calculate y = A' * x + y */
#include "cs.h"
int main(int argc, char * argv[])
{
	cs *T, *A ;
	int m = 3, n = 3 ;
	m = atoi(argv[1]); /* # of row */
	n = atoi(argv[2]); /* # of col */
	int i = 0 ;
	csi flag = 0 ;
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
	for(i=0; i<n; i++)
	{
		fscanf(fp, "%lf", &(x[i])) ;
	}
	/* read y0 from file */
	fp = fopen(fileVectorY, "r") ;
	for(i=0; i<m; i++)
	{
		fscanf(fp, "%lf", &(y[i])) ;
	}
	/* print x */
	printf("x = \n") ;
	for(i=0; i<n; i++)
	{
		printf("%lf\n", x[i]) ;
	}
	/* print y0 */
	printf("y0 = \n") ;
	for(i=0; i<m; i++)
	{
		printf("%lf\n", y[i]) ;
	}
	/* calculate y = A' * x + y */
	flag = cs_gatxpy(A, x, y) ;
	if(!flag) 
	{
		printf("fail, quit...\n") ;
		return 0;
	}
	/* print y */
	printf("y = \n") ;
	for(i=0; i<m; i++)
	{
		printf("%lf\n", y[i]) ;
	}
	/* release */
	printf("release...\n") ;
	cs_spfree(A) ;
	free(x) ;
	free(y) ;
	printf("release done.\n") ;

	return 0;
}

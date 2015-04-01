/* 20150402 */
/* test cs_gaxpy_triplet */
/* y = T*x+y */
#include "cs.h"
int main(int argc, char * argv[])
{
	cs *T ;
	int i = 0 ;
	csi m = 3, n = 3 ;
	m = atoi(argv[1]) ;
	n = atoi(argv[2]) ;
	csi flag = 0 ;
	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
	char fileVectorX[256] = "fileVectorX" ;
	char fileVectorY[256] = "fileVectorY" ;
	/* allocate x, y */
	double *x = (double *)malloc(sizeof(double) * n) ;
	double *y = (double *)malloc(sizeof(double) * m) ;
	/* read T from file */
	fp = fopen(fileMatrix, "r") ;
	T = cs_load(fp) ; /* load triplet matrix T from stdin */
	fclose(fp);
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
	/* calculate y = T * x + y */
	flag = cs_gaxpy_triplet(T, x, y) ;
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
	cs_spfree(T) ;
	free(x) ;
	free(y) ;
	printf("release done.\n") ;

	return 0 ;
}

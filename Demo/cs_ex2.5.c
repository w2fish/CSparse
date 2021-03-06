/* 20150330 */
/* test cs_entry_submatrix */
#include "cs.h"
int main()
{
	cs *T ;
	double **D ;
	int i = 0, j = 0 ;
	int k = 3 ; /* size of subMatrix k-by-k */
	csi flag = 0 ;
	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
	char fileDenseMatrix[256] = "fileDenseMatrix" ;
	char fileVectorX[256] = "fileVectorX" ;
	char fileVectorY[256] = "fileVectorY" ;
	/* allocate x, y */
	int *x = (int *)malloc(sizeof(int) * k) ;
	int *y = (int *)malloc(sizeof(int) * k) ;
	/* allocate D */
	D = (double **)malloc(sizeof(double) * k) ;
	for(i=0; i<k; i++)
	{
		D[i] = (double *)malloc(sizeof(double) * k) ;
	}
	/* read T from file */
	fp = fopen(fileMatrix, "r") ;
	T = cs_load(fp) ; /* load triplet matrix T from stdin */
	fclose(fp);
	printf("T = \n") ; cs_print(T, 0) ;
	/* read D from file */
	fp = fopen(fileDenseMatrix, "r") ;
	for(i=0; i<k; i++)
	{
		for(j=0; j<k; j++)
		{
			fscanf(fp, "%lf", &(D[i][j])) ;
		}
	}			
	fclose(fp);
	/* read x from file */
	fp = fopen(fileVectorX, "r") ;
	for(i=0; i<k; i++)
	{
		fscanf(fp, "%d", &(x[i])) ;
	}
	/* read y from file */
	fp = fopen(fileVectorY, "r") ;
	for(i=0; i<k; i++)
	{
		fscanf(fp, "%d", &(y[i])) ;
	}
	/* print x */
	printf("x = \n") ;
	for(i=0; i<k; i++)
	{
		printf("%d\n", x[i]) ;
	}
	/* print y */
	printf("y = \n") ;
	for(i=0; i<k; i++)
	{
		printf("%d\n", y[i]) ;
	}
	/* insert submatrix D in T */
	flag = cs_entry_submatrix(T, k, x, y, D) ;
	if(!flag) printf("Bad...\n") ;
	/* print new T */
	printf("new T = \n") ; cs_print(T, 0) ;
	/* release */
	printf("release...\n") ;
	cs_spfree(T) ;
	free(x) ;
	free(y) ;
	for(i=0; i<k; i++)
	{
		free(D[i]) ;
	}
	free(D) ;	
	printf("release done.\n") ;

	return 0 ;
}

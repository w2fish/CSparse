/* 20150412 */
/* test cs_gaxpym */
/* Y = A * X + Y */
/* X, Y is dense matrix */
/* 3 versions: [1] X, Y col major */
/*             [2] X, Y row major */
/*             [3] X, Y col major but operate 32 col at a t */
/* paramters: major: COL, ROW, COL1 */
/*            M: row # of Y */
/*            N: col # of A */
/*            K: col # of Y */
/* running time comparison for m=3000, n=6000, K=1000: */
/* [1]: 100%      [2] 90%      [3] 139% */
#include "cs.h"
#include <time.h>
#define COL		0
#define ROW		1
#define COL1	2
int main(int argc, char * argv[])
{
	clock_t t ;
	int print = atoi(argv[1]) ;
	cs *T = NULL, *A = NULL ;
	csi m, n, i, j, flag ;
	m = (csi)atoi(argv[2]) ;
	n = (csi)atoi(argv[3]) ;
	csi K = (csi)atoi(argv[4]) ;    /* K: col # of Y */
	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
	char fileVectorX[256] = "fileVectorX" ;
	char fileVectorY[256] = "fileVectorY" ;
	int major = atoi(argv[5]) ;
	/* load A */
	fp = fopen(fileMatrix, "r") ;
	if (!fp)
	{
		printf("open fileMatrix fail, quit\n") ; return 0 ;
	}
	T = cs_load(fp) ;
	fclose(fp) ;
	if (!T)
	{
		printf("load T fail, quit\n") ; return 0 ;
	}
	A = cs_compress(T) ;
	if (1)
	{
		printf("T = \n") ; cs_print(T, 1) ;
		printf("A = \n") ; cs_print(A, 1) ;
	}
	T = cs_spfree(T) ;
	/* allocate X, Y */
	double *X = (double *)malloc(sizeof(double) * n*K) ;
	double *Y = (double *)malloc(sizeof(double) * m*K) ;
	double *Xrow = (double *)malloc(sizeof(double) * n*K) ;
	double *Yrow = (double *)malloc(sizeof(double) * m*K) ;
	double *X1 = (double *)malloc(sizeof(double) * n*K) ;
	double *Y1 = (double *)malloc(sizeof(double) * m*K) ;
	/* read X from file, col major */
	fp = fopen(fileVectorX, "r") ;
	for(i=0; i<n*K; i++)
	{
		fscanf(fp, "%lf", &(X[i])) ;
	}
	/* copy X to Xrow, row major */
	for (j=0; j<K; j++)
	{
		for (i=0; i<n; i++)
		{
			Xrow[i*K + j] = X[j*n + i] ;
		}
	}
	/* copy X to X1, col major */
	for(i=0; i<n*K; i++)
	{
		X1[i] = X[i] ;
	}
	/* read Y from file */
	fp = fopen(fileVectorY, "r") ;
	for(i=0; i<m*K; i++)
	{
		fscanf(fp, "%lf", &(Y[i])) ;
	}
	/* copy Y to Yrow, row major */
	for (j=0; j<K; j++)
	{
		for (i=0; i<m ; i++)
		{
			Yrow[i*K + j] = Y[j*m + i] ;
		}
	}
	/* copy Y to Y1, col major */
	for (i=0; i<m*K; i++)
	{
		Y1[i] = Y[i] ;
	}
	/* print */
	if (print)
	{
		printf("X = \n") ;
		for (i=0; i<n; i++)
		{
			for (j=0; j<K; j++)
			{
				printf("%4.0lf\t", X[j*n + i]) ;
			}
			printf("\n") ;
		}
		printf("Xrow = \n") ;
		for (i=0; i<n; i++)
		{
			for (j=0; j<K; j++)
			{
				printf("%4.0lf\t", Xrow[i*K + j]) ;
			}
			printf("\n") ;
		}
		printf("X1 = \n") ;
		for (i=0; i<n; i++)
		{
			for (j=0; j<K; j++)
			{
				printf("%4.0lf\t", X1[j*n + i]) ;
			}
			printf("\n") ;
		}
		printf("Y = \n") ;
		for (i=0; i<m; i++)
		{
			for (j=0; j<K; j++)
			{
				printf("%4.0lf\t", Y[j*m + i]) ;
			}
			printf("\n") ;
		}
		printf("Yrow = \n") ;
		for (i=0; i<m; i++)
		{
			for (j=0; j<K; j++)
			{
				printf("%4.0lf\t", Yrow[i*K + j]) ;
			}
			printf("\n") ;
		}
		printf("Y1 = \n") ;
		for (i=0; i<m; i++)
		{
			for (j=0; j<K; j++)
			{
				printf("%4.0lf\t", Y1[j*m + i]) ;
			}
			printf("\n") ;
		}
	}
	/* calculate Y = A * X + Y */
	t = clock() ;
	if (major == COL) flag = cs_gaxpym(major, m, n, K, A, X, Y) ;
	else if (major == ROW) flag = cs_gaxpym(major, m, n, K, A, Xrow, Yrow) ;
	else if (major == COL1) flag = cs_gaxpym(major, m, n, K, A, X1, Y1) ;
	t = clock() - t ;
	printf("major = %d\tt = %lf s\n", major, (double)t/CLOCKS_PER_SEC) ;
	if (!flag) 
	{
		printf("major = %d, cs_gaxpym fail, quit\n", major) ; return 0 ;
	}
	/* print */
	if (print)
	{
		printf("Y = \n") ;
		for (i=0; i<m; i++)
		{
			for (j=0; j<K; j++)
			{
				printf("%4.0lf\t", Y[j*m + i]) ;
			}
			printf("\n") ;
		}
		printf("Yrow = \n") ;
		for (i=0; i<m; i++)
		{
			for (j=0; j<K; j++)
			{
				printf("%4.0lf\t", Yrow[i*K + j]) ;
			}
			printf("\n") ;
		}
		printf("Y1 = \n") ;
		for (i=0; i<m; i++)
		{
			for (j=0; j<K; j++)
			{
				printf("%4.0lf\t", Y1[j*m + i]) ;
			}
			printf("\n") ;
		}
	}
	/* release */
	A = cs_spfree(A) ;
	X = cs_free(X) ;
	Xrow = cs_free(Xrow) ;
	X1 = cs_free(X1) ;
	Y = cs_free(Y) ;
	Yrow = cs_free(Yrow) ;
	Y1 = cs_free(Y1) ;
	return 0 ;
}


/* 20150401 */
/* create cs matrix in triplet form, write to fileMatrix */
/* command: test_create_fileMatrix m n randomOrNot */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char * argv[])
{
	/* initialize random seed */
	srand(time(NULL)) ;

	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
	int m, n, i, j, t, ti, tj, random ;
	m = atoi(argv[1]) ;
	n = atoi(argv[2]) ;
	random = atoi(argv[3]) ;
	/* write fileMatrix */
	fp = fopen(fileMatrix, "w") ;
	if(!fp)
	{
		printf("open fileMatrix to write fail, quit\n") ;
		return 1 ;
	}
	if (random)
	{
		for(i=0; i<m/10; i++)
		{
			for(j=0; j<n/10; j++)
			{
				t = rand() % 10 -4  ;
				ti = rand() % m ;
				tj = rand() % n ;
				fprintf(fp, "%d\t%d\t%d\n", ti, tj, t) ;
			}
		}
	}
	else
	{
		for(i=0; i<m; i++)
		{
			for(j=0; j<n; j++)
			{
				t = rand() % 10 -4  ;
				ti = rand() % m ;
				tj = rand() % n ;
				fprintf(fp, "%d\t%d\t%d\n", i, j, t) ;
			}
		}
	}
	fclose(fp) ;

	return 0 ;
}


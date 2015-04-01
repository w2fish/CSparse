/* 20150401 */
/* create cs matrix in triplet form, write to fileMatrix */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char * argv[])
{
	/* initialize random seed */
	srand(time(NULL)) ;

	FILE *fp ;
	char fileMatrix[256] = "fileMatrix" ;
	int m, n, i, j, t, ti, tj ;
	m = atoi(argv[1]) ;
	n = atoi(argv[2]) ;
	/* write fileMatrix */
	fp = fopen(fileMatrix, "w") ;
	if(!fp)
	{
		printf("open fileMatrix to write fail, quit\n") ;
		return 1 ;
	}
	for(i=0; i<m; i++)
	{
		for(j=0; j<n; j++)
		{
			t = rand() % 10 -4  ;
			ti = rand() % m ;
			tj = rand() % n ;
			fprintf(fp, "%d\t%d\t%d\n", ti, tj, t) ;
		}
	}
	fclose(fp) ;

	return 0 ;
}


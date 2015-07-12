/* 20150712 */
/* test cs_lsolvesp */
/* solve Lx = b */
/* L, x, b are sparse, L comes from Cholesky factorization */
/* the elimination tree is known, pass as parameter*/
#include <stdlib.h>
#include "cs.h"
int main ()
{
	FILE *fp = NULL ;
	char fileMatrix[256] = "fileMatrix" ;
	char fileVectorX[256] = "fileVectorX" ;
	char fileParent[256] = "parent" ;
	cs *T = NULL, *L = NULL, *b = NULL, *x = NULL ;
	csi n, j, flag ;
	int temp ;
	csi *parent = NULL ;
	/* load L */
	fp = fopen(fileMatrix, "r") ;
	if (!fp) {
		printf("can't open %s, quit\n", fileMatrix) ;
		return 0 ;
	}
	T = cs_load(fp) ;
	fclose(fp) ;
	if (!T) {
		printf("load T fail, quit\n") ;
		return 0 ;
	}
	L = cs_compress(T) ;
	L = cs_sort(L) ; /* sort column wise */
	T = cs_spfree(T) ;
	n = L->n ;
	/* print L */
	printf("L:\n") ;
	cs_print(L, 0) ;
	/* load b */
	fp = fopen(fileVectorX, "r") ;
	if (!fp) {
		printf("can't open %s, quit\n", fileVectorX) ;
		return 0 ;
	}
	T = cs_load(fp) ;
	printf("b_T:\n") ;
	cs_print(T, 0) ;
	fclose(fp) ;
	if (!T) {
		printf("load T fail, quit\n") ;
		return 0 ;
	}
	b = cs_compress(T) ;
	T = cs_spfree(T) ;
	b->m = n ;
	/* print b */
	printf("b:\n") ;
	cs_print(b, 0) ;
	/* read parent */
	parent = cs_malloc(n, sizeof(csi));
	fp = fopen(fileParent, "r") ;
	if (!fp) {
		printf("can't open %s, quit\n", fileParent) ;
		return -1 ;
	}
	for (j=0 ; j<n ; j++) {
		fscanf(fp, "%d" , &temp) ;
		parent[j] = temp ;
	}
	/* solve Lx = b */
	x = cs_lsolvesp(L, b, parent) ;
	if (!x) {
		printf("cs_lsolvesp failed\n") ;
		return 0 ;
	}
	x = cs_sort(x) ;
	/* print x */
	cs_print(x, 0) ;
	/* release */
	x = cs_spfree(x) ;
	b = cs_spfree(b) ;
	L = cs_spfree(L) ;
	parent = cs_free(parent) ;

	return 0 ;
}

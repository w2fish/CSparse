/* 20150707 */
/* test cs_ereach2 */
/* Another version of cs_ereach to implement O(L) time algorithm */
/* compute e-tree, # of entry in each row/col */
/* use only A and O(n) additional workspace */
/* do NOT modify A */
#include <stdlib.h>
#include "cs.h"
csi main()
{
	FILE *fp = NULL ;
	char fileMatrix[256] = "fileMatrix" ;
	cs *T = NULL, *A = NULL ;
	csi n, j, p ;
	csi *parent = NULL, *s = NULL, *rc = NULL, *cc = NULL ;
	csi *w = NULL ;
	/* load A */
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
	A = cs_compress(T) ;
	T = cs_spfree(T) ;
	n = A->n ;
	/* prcsi A */
	printf("A:\n") ;
	cs_print(A, 0) ;
	/* initialize */
	parent = cs_calloc(n, sizeof(csi)) ;
	s = cs_calloc(n, sizeof(csi)) ;
	rc = cs_calloc(n, sizeof(csi)) ;
	cc = cs_calloc(n, sizeof(csi)) ;
	w = cs_calloc(n, sizeof(csi)) ;
	for (j=0 ; j<n ; j++) parent[j] = -1 ;
	/* call cs_ereach2 */
	for (j=0 ; j<n ; j++) {
		cs_ereach2(A, j, parent, s, w, rc, cc) ;
	}
	/* prcsi result */
	printf("\nparent\n");
	for (j=0; j<n; j++) printf("%d  ", parent[j]);
	printf("\nrc\n");
	for (j=0; j<n; j++) printf("%d  ", rc[j]);
	printf("\ncc\n");
	for (j=0; j<n; j++) printf("%d  ", cc[j]);
	printf("\n\n") ;
	/* free */
	A = cs_spfree(A) ;
	parent = cs_free(parent) ;
	s = cs_free(s) ;
	w = cs_free(w) ;
	rc = cs_free(rc) ;
	cc = cs_free(cc) ;

    return 0;
}

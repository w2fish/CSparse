/* 20150402 */
/* Tim.D. book, ex2.9 */
/* create CSC matrix from triplet matrix */
/* sorted columns, no duplicate, no numerically zero entry */
#include "cs.h"
cs *cs_compress2(const cs *T)
{
	cs *C = NULL, *Cs = NULL ;
	csi nz = T->nz, ok ;
	C = cs_compress(T) ; /* compress */
	ok = cs_dupl(C) ; /* remove duplicate */
	Cs = cs_sort(C) ; /* sort */
	nz = cs_dropzeros(Cs) ;

	/* release */
	cs_spfree(C) ;

	return Cs ;
}

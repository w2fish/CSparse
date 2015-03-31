/* 20150331 */
/* Tim.D. book, ex2.7 */
/* sort cs matrix column-wise by 2 transpose, this is really cool */
#include "cs.h"
cs *cs_sort(cs *A)
{
	cs *At, *Att ;

	/* method 1 */
	/*At = cs_transpose(A, 1) ;
	Att = cs_transpose(At, 1) ;
	cs_spfree(At) ; */

	/* method 2 */
	Att = cs_transpose(cs_transpose(A, 1), 1) ;

	return Att ;
}

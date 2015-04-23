#include "cs.h"
void Insert(csi x, List L, Position P)
{
	Position TmpCell ;
	TmpCell = malloc(sizeof(struct Node)) ;
	if (TmpCell == NULL)
	{
		printf("allocate Node fail, quit\n") ; return NULL ;
	}
	TmpCell->x = x ;
	TmpCell->Next = P->Next ;
	P->Next = TmpCell ;
}
void DeleteList(List L)
{
	Position P, Tmp ;
	P = L->Next ; /* header assumed */
	L->Next = NULL ;
	while(P != NULL)
	{
		Tmp = P->Next ;
		free(P) ;
		P = Tmp ;
	}
}
List MakeEmpty(List L)
{
	L = malloc(sizeof(struct Node)) ;
	if (L== NULL)
	{
		printf("allocate Node fail, quit\n") ; return NULL ;
	}
	L->Next = NULL ;
	return L ;
}
int IsEmpty(List L)
{
	return L->Next == NULL ;
}
/* return the first node after delete */
List DeleteFirst(List L) 
{
	if (IsEmpty(L)) return NULL ;
	Position P, Tmp ;
	Tmp = L->Next ;
	P = Tmp->Next ;
	L->Next = P ;
	free(Tmp) ;
	return L ;
}


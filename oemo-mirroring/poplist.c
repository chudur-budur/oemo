#include <stdio.h>
#include <stdlib.h>
#include "global.h"

pop_list* new_list()
{
	pop_list* plist = (pop_list*)malloc(sizeof(pop_list));
	if(plist == NULL)
	{
		fprintf(stderr, "indlist.c: Coudn't allocate a \'list\' in new_list()\n");
		exit(1);
	}
	plist->head = END ;
	plist->size = 0 ;
	return plist ;
}

void free_list(pop_list *plist)
{
	node *curr, *prev ;
	if(!is_empty(plist))
	{
		curr = plist->head ;
		while(curr != END)
		{
			prev = curr ;
			deallocate_memory_ind(curr->ind);
			free(curr->ind);
			curr = curr->next ;
			free(prev);
		}
	}
	free(plist);
}

int is_empty(pop_list *plist)
{
	if(plist->head == END)
		return TRUE ;
	else
		return FALSE ;
}

void push_front(pop_list *plist, individual *ind)
{
	node *n ;
	n = (node*)malloc(sizeof(node));
	if(n == NULL)
	{
		fprintf(stderr, "Couldn't allocate \'node\' in push_front()\n");
		exit(1);
	}
	n->ind = ind ;
	n->next = plist->head ;
	plist->head = n ;
	plist->size++;
}

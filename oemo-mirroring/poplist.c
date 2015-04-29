#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "rand.h"

int nreal;
int nbin;
int nobj;
int ncon;
double *min_realvar;
double *max_realvar;

pop_list* new_list()
{
	pop_list* plist = (pop_list*)malloc(sizeof(pop_list));
	if(plist == NULL)
	{
		fprintf(stderr, "indlist.c: Coudn't allocate a \'list\' in new_list()\n");
		exit(1);
	}
	plist->head = END ;
	plist->tail = END ;
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
	if(plist->head == END && plist->tail == END)
		return TRUE ;
	else
		return FALSE ;
}

void push_back(pop_list *plist, individual *ind)
{
	node *n ;
	n = (node*)malloc(sizeof(node));
	if(n == NULL)
	{
		fprintf(stderr, "Couldn't allocate \'node\' in push_front()\n");
		exit(1);
	}
	n->next = END ;
	n->prev = END ;
	n->ind = (individual*)malloc(sizeof(individual));
	allocate_memory_ind(n->ind);
	indcpy(ind, n->ind);
	if(is_empty(plist))
	{
		plist->head = n ;
		plist->tail = n ;
	}
	else
	{
		plist->tail->next = n ;
		n->prev = plist->tail ;
		plist->tail = plist->tail->next ;
	}
	plist->size++;
}

void erase(pop_list *lst, node *ptr)
{
	node *temp = NULL;
	if(!is_empty(lst))
	{
		if(ptr == lst->head)
		{
			temp = lst->head ;
			lst->head = lst->head->next ;
			lst->head->prev = END ;
		}
		else if(ptr == lst->tail)
		{
			temp = lst->tail ;
			lst->tail = lst->tail->prev ;
			lst->tail->next = END ;	
		}
		else
		{
			temp = ptr ;
			ptr->prev->next = ptr->next ;
			ptr->next->prev = ptr->prev ;	
		}
		deallocate_memory_ind(temp->ind);
		free(temp->ind);
		free(temp);
	}
}

/*
int main()
{
	int i ;
	nreal = 2 ;
	nbin = 0 ;
	nobj = 2 ;
	ncon = 0 ;
	min_realvar = (double*)malloc(sizeof(double) * nreal);
	max_realvar = (double*)malloc(sizeof(double) * nreal);
	for(i = 0 ; i < nreal ; i++)
	{
		min_realvar[i] = 0.0 ;
		max_realvar[i] = 1.0 ;
	}
	seed = 0.12345 ;
	randomize();
	
	pop_list *lst = new_list();
	node *ptr = NULL ;
	individual *ind = NULL ;
	
	fprintf(stdout, "is_empty? %d\n", is_empty(lst));

	for(i = 0 ; i < 4 ; i++) 
	{
		ind = (individual*)malloc(sizeof(individual));
		allocate_memory_ind(ind);
		initialize_ind(ind);
		push_back(lst, ind);
		deallocate_memory_ind(ind);
		free(ind);
	}
	dump_population_list(lst, stdout); fprintf(stdout, "\n");


	ptr = lst->head->next ;
	erase(lst, ptr);
	dump_population_list(lst, stdout); fprintf(stdout, "\n");
	
	ptr = lst->head ;
	erase(lst, ptr);
	dump_population_list(lst, stdout); fprintf(stdout, "\n");
	
	ptr = lst->tail ;
	erase(lst, ptr);
	dump_population_list(lst, stdout); fprintf(stdout, "\n");

	free_list(lst);
}*/

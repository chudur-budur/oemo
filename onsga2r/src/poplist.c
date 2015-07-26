#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "rand.h"
#include "poplist.h"
#include "misc.h"

int nreal;
int nbin;
int nobj;
int ncon;
double *min_realvar;
double *max_realvar;

/**
typedef struct node node ;

struct node {
	individual *ind ;
	node *next ;
	node *prev ;
};

typedef struct {
	node *head ;
	node *tail ;
	int size ;
} pop_list ;
*/

pop_list* new_list()
{
	pop_list* lst = (pop_list*)malloc(sizeof(pop_list));
	if(lst == NULL)
	{
		fprintf(stderr, "indlist.c: Coudn't allocate a \'list\' in new_list()\n");
		exit(1);
	}
	lst->head = END ;
	lst->tail = END ;
	lst->size = 0 ;
	return lst ;
}

int is_empty(pop_list *lst)
{
	if(lst->head == END && lst->tail == END)
		return TRUE ;
	else
		return FALSE ;
}

void push_back(pop_list *lst, individual *ind)
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
	if(is_empty(lst))
	{
		lst->head = n ;
		lst->tail = n ;
	}
	else
	{
		lst->tail->next = n ;
		n->prev = lst->tail ;
		lst->tail = lst->tail->next ;
	}
	lst->size++;
}

node* pop_back(pop_list *lst)
{
	node *temp = NULL ;
	if(!is_empty(lst))
	{
		if(lst->head != lst->tail)
		{
			temp = lst->tail ;
			lst->tail->prev->next = END ;
			lst->tail = lst->tail->prev ;
			temp->prev = END ;
		}
		else
		{
			temp = lst->head ;
			lst->head = END ;
			lst->tail = END ;
		}
		lst->size-- ;
		return temp ;
	}
	else
		return NULL ;
}

node* pop_front(pop_list *lst)
{
	node *temp = NULL ;
	if(!is_empty(lst))
	{
		if(lst->head != lst->tail)
		{
			temp = lst->head ;
			lst->head->next->prev = END ;
			lst->head = lst->head->next ;
			temp->next = END ;
		}
		else
		{
			temp = lst->head ;
			lst->head = END ;
			lst->tail = END ;
		}
		lst->size--;
		return temp ;
	}
	else
		return NULL ;
}

node* top(pop_list *lst)
{
	if(!is_empty(lst))
		return lst->head ;
	else
		return NULL ;
}

node* erase(pop_list *lst, node *ptr)
{
	node *temp = NULL;
	if(!is_empty(lst))
	{
		if(lst->head == lst->tail)
		{
			temp = lst->head ;
			lst->head = END ;
			lst->tail = END ;
			ptr = END ;
			lst->size-- ;
		}
		else
		{
			if(ptr == lst->head)
			{
				ptr = ptr->next ;
				temp = pop_front(lst);
			}
			else if(ptr == lst->tail)
			{
				ptr = ptr->prev ;
				temp = pop_back(lst) ;
			}
			else
			{
				temp = ptr ;
				ptr->prev->next = ptr->next ;
				ptr->next->prev = ptr->prev ;
				ptr = ptr->next ;
				temp->next = END ;
				temp->prev = END ;
				lst->size-- ;
			}
		}
		deallocate_memory_ind(temp->ind);
		free(temp->ind);
		free(temp);
		return ptr ;
	}
	return ptr ;
}

void make_empty(pop_list *lst)
{
	int i, size ;
	node *temp ;
	size = lst->size ;
	if(!is_empty(lst))
	{
		for(i = 0 ; i < size ; i++)
		{
			temp = pop_front(lst);
			deallocate_memory_ind(temp->ind);
			free(temp->ind);
			free(temp);
		}
	}
	lst->head = END ;
	lst->tail = END ;
	lst->size = 0 ;
}

void free_list(pop_list *lst)
{
	make_empty(lst);
	free(lst);
}

void dump_pop_list(pop_list *lst, FILE *fpt)
{
	node *curr ;
	for(curr = lst->head; curr != END; curr = curr->next)
	{
		if(fpt == stdout)
			dumpf_individual(curr->ind, fpt);
		else
			dump_individual(curr->ind, fpt);
	}
	return ;
}

void deep_copy(pop_list *src, pop_list *dest)
{
	node *ptr = NULL ;
	if(!is_empty(dest))
		make_empty(dest);
	for(ptr = src->head; ptr != END ; ptr = ptr->next)
		push_back(dest, ptr->ind);
}

void to_list(population *pop, int size, pop_list *lst)
{
	int i ;
	for(i = 0 ; i < size ; i++)
		push_back(lst, &(pop->ind[i]));
}

void to_array(pop_list *lst, population *pop, int size)
{
	int i ;
	node *curr ;
	for(curr = lst->head, i = 0 ; curr != END ; curr = curr->next, i++);
	indcpy(curr->ind, &(pop->ind[i]));
}

int is_member(individual *ind, pop_list *lst,
              int (*comparator)(individual *i1, individual *i2))
{
	int member = 0 ;
	node *ptr ;
	if(is_empty(lst))
		return member ;
	else
	{
		for(ptr = lst->head ; ptr != END ; ptr = ptr->next)
			if((*comparator)(ind, ptr->ind))
			{
				member = 1 ;
				break ;
			}
	}
	return member ;
}

/**
 * All the "pointer only" operations
 */
void push_back_ptr(pop_list *lst, individual *ind)
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
	n->ind = ind ;
	if(is_empty(lst))
	{
		lst->head = n ;
		lst->tail = n ;
	}
	else
	{
		lst->tail->next = n ;
		n->prev = lst->tail ;
		lst->tail = lst->tail->next ;
	}
	lst->size++;
}

node* erase_ptr(pop_list *lst, node *ptr)
{
	node *temp = NULL;
	if(!is_empty(lst))
	{
		if(lst->head == lst->tail)
		{
			temp = lst->head ;
			lst->head = END ;
			lst->tail = END ;
			ptr = END ;
			lst->size-- ;
		}
		else
		{
			if(ptr == lst->head)
			{
				ptr = ptr->next ;
				temp = pop_front(lst);
			}
			else if(ptr == lst->tail)
			{
				ptr = ptr->prev ;
				temp = pop_back(lst) ;
			}
			else
			{
				temp = ptr ;
				ptr->prev->next = ptr->next ;
				ptr->next->prev = ptr->prev ;
				ptr = ptr->next ;
				temp->next = END ;
				temp->prev = END ;
				lst->size-- ;
			}
		}
		temp->ind = NULL ;
		free(temp);
		return ptr ;
	}
	return ptr ;
}

void make_empty_ptr(pop_list *lst)
{
	int i, size ;
	node *temp ;
	size = lst->size ;
	if(!is_empty(lst))
	{
		for(i = 0 ; i < size ; i++)
		{
			temp = pop_front(lst);
			temp->ind = NULL;
			free(temp);
		}
	}
	lst->head = END ;
	lst->tail = END ;
	lst->size = 0 ;
}

void free_list_ptr(pop_list *lst)
{
	make_empty_ptr(lst);
	free(lst);
}

void deep_copy_ptr(pop_list *src, pop_list *dest)
{
	node *ptr ;
	if(!is_empty(dest))
		make_empty_ptr(dest);
	for(ptr = src->head; ptr != END ; ptr = ptr->next)
		push_back_ptr(dest, ptr->ind);
}

void to_list_ptr(population *pop, int size, pop_list *lst)
{
	int i ;
	for(i = 0 ; i < size ; i++)
		push_back_ptr(lst, &(pop->ind[i]));
}


void nl()
{
	fprintf(stdout, "\n");
}
void sp(char *str)
{
	fprintf(stdout, "%s", str) ;
}

void deep_test(population *pop, pop_list *lst)
{
	int i ;
	node *ptr ;

	lst = new_list();

	fprintf(stdout, "is_empty? %d\n", is_empty(lst));
	dump_pop_list(lst, stdout);
	nl();

	for(i = 0 ; i < 6 ; i++) push_back(lst, &(pop->ind[i]));
	fprintf(stdout, "list %d:\n", lst->size);
	dump_pop_list(lst, stdout);
	nl();

	sp("popping sequence:\n");
	ptr = pop_back(lst) ;
	dumpf_individual(ptr->ind, stdout);
	deallocate_memory_ind(ptr->ind);
	free(ptr->ind);
	free(ptr);
	ptr = pop_front(lst) ;
	dumpf_individual(ptr->ind, stdout);
	deallocate_memory_ind(ptr->ind);
	free(ptr->ind);
	free(ptr);
	fprintf(stdout, "list %d:\n", lst->size);
	dump_pop_list(lst, stdout);
	fprintf(stdout, "\n");
	fprintf(stdout, "is_empty? %d\n", is_empty(lst));

	ptr = lst->head ;
	ptr = erase(lst, ptr);
	fprintf(stdout, "list %d:\n", lst->size);
	dump_pop_list(lst, stdout);
	nl();
	sp("ptr: ");
	dumpf_individual(ptr->ind, stdout);

	ptr = lst->head->next ;
	ptr = erase(lst, ptr);
	fprintf(stdout, "list %d:\n", lst->size);
	dump_pop_list(lst, stdout);
	nl();
	sp("ptr: ");
	dumpf_individual(ptr->ind, stdout);

	ptr = lst->tail ;
	ptr = erase(lst, ptr);
	fprintf(stdout, "list %d:\n", lst->size);
	dump_pop_list(lst, stdout);
	nl();
	sp("ptr: ");
	dumpf_individual(ptr->ind, stdout);


	for(i = 0 ; i < 6 ; i++) push_back(lst, &(pop->ind[i]));
	fprintf(stdout, "list %d:\n", lst->size);
	dump_pop_list(lst, stdout);
	fprintf(stdout, "\n");
	make_empty(lst);
	fprintf(stdout, "list %d:\n", lst->size);
	dump_pop_list(lst, stdout);
	nl();
	free_list(lst);
}

void shallow_test(population *pop, pop_list *lst)
{
	int i ;
	node *ptr ;

	lst = new_list();

	fprintf(stdout, "is_empty? %d\n", is_empty(lst));
	dump_pop_list(lst, stdout);
	nl();

	for(i = 0 ; i < 6 ; i++) push_back_ptr(lst, &(pop->ind[i]));
	fprintf(stdout, "list %d:\n", lst->size);
	dump_pop_list(lst, stdout);
	nl();

	sp("popping sequence:\n");
	ptr = pop_back(lst) ;
	dumpf_individual(ptr->ind, stdout);
	ptr->ind = NULL;
	free(ptr);
	ptr = pop_front(lst) ;
	dumpf_individual(ptr->ind, stdout);
	ptr->ind = NULL;
	free(ptr);
	fprintf(stdout, "list %d:\n", lst->size);
	dump_pop_list(lst, stdout);
	fprintf(stdout, "\n");
	fprintf(stdout, "is_empty? %d\n", is_empty(lst));

	ptr = lst->head ;
	ptr = erase_ptr(lst, ptr);
	fprintf(stdout, "list %d:\n", lst->size);
	dump_pop_list(lst, stdout);
	nl();
	sp("ptr: ");
	dumpf_individual(ptr->ind, stdout);

	ptr = lst->head->next ;
	ptr = erase_ptr(lst, ptr);
	fprintf(stdout, "list %d:\n", lst->size);
	dump_pop_list(lst, stdout);
	nl();
	sp("ptr: ");
	dumpf_individual(ptr->ind, stdout);

	ptr = lst->tail ;
	ptr = erase_ptr(lst, ptr);
	fprintf(stdout, "list %d:\n", lst->size);
	dump_pop_list(lst, stdout);
	nl();
	sp("ptr: ");
	dumpf_individual(ptr->ind, stdout);


	for(i = 0 ; i < 6 ; i++) push_back_ptr(lst, &(pop->ind[i]));
	fprintf(stdout, "list %d:\n", lst->size);
	dump_pop_list(lst, stdout);
	fprintf(stdout, "\n");
	make_empty_ptr(lst);
	fprintf(stdout, "list %d:\n", lst->size);
	dump_pop_list(lst, stdout);
	nl();
	free_list_ptr(lst);
}

/*
int main()
{
	int i;
	pop_list *lst ;
	population pop ;

	popsize = 10 ;
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
	allocate_memory_pop(&pop, popsize);
        initialize_pop(&pop);

	deep_test(&pop,lst);
	shallow_test(&pop, lst);

	deallocate_memory_pop(&pop, popsize);
	free(min_realvar);
	free(max_realvar);
}*/

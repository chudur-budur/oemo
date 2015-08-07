# ifndef _POPLIST_H_
# define _POPLIST_H_

# include <stdio.h>
# include "global.h"

/**
 * Some functions for list operations.
 * defined in poplist.c
 */
#define END NULL
#define TRUE 1
#define FALSE 0

typedef struct node node ;

struct node
{
	individual *ind ;
	node *next ;
	node *prev ;
};

typedef struct
{
	node *head ;
	node *tail ;
	int size ;
} pop_list ;

pop_list* new_list();
int is_empty(pop_list *lst);
void push_back(pop_list *lst, individual *ind);
node* pop_back(pop_list *lst);
node* pop_front(pop_list *lst);
node* top(pop_list *lst);
node* erase(pop_list *lst, node *ptr);
void make_empty(pop_list* lst);
void free_list(pop_list* lst);
void deep_copy(pop_list *src, pop_list *dest);
void to_list(population *pop, int size, pop_list *lst);
void to_array(pop_list *lst, population *pop, int size);
int is_member(individual *ind, pop_list *lst,
              int (*comparator)(individual *i1, individual *i2));

void push_back_ptr(pop_list *lst, individual *ind);
node* erase_ptr(pop_list *lst, node *ptr);
void make_empty_ptr(pop_list *lst);
void free_list_ptr(pop_list* lst);
void deep_copy_ptr(pop_list *src, pop_list *dest);
void to_list_ptr(population *pop, int size, pop_list *lst);
void dump_pop_list(FILE *fpt, pop_list *lst);
void evaluate_pop_list(pop_list *pop);

# endif

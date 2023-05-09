#include "int_xor_list.h"

static t_ixmnode* xor_func(t_ixmnode* prev, t_ixmnode* next)
{
    return ((t_ixmnode*)((uintptr_t)prev ^ (uintptr_t)next));
}

static t_ixmnode *new_ixmnode(int nbr)
{
	t_ixmnode *new;

	new = malloc(sizeof(t_ixmnode));
	if (!new)
		return (NULL);
	new->data = nbr;
	new->xor_ptr = NULL;
	return (new);
}

t_ixmlist *ixmlist_new(void)
{
	t_ixmlist *list;

	list = malloc(sizeof(*list));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->tail = NULL;
	list->len = 0;
	return (list);
}

void ixmlist_in_head(t_ixmlist* list, int data)
{
	t_ixmnode* new_node;

	if (!list)
		return ;
	new_node = new_ixmnode(data);
	if (!new_node)
		return ;
	new_node->xor_ptr = list->head;
	if (list->head)
		list->head->xor_ptr = xor_func(new_node, list->head->xor_ptr);
	else
		list->tail = new_node;
	list->head = new_node;
	++(list->len);
}

void ixmlist_in_tail(t_ixmlist* list, int data)
{
	t_ixmnode* new_node;

	if (!list)
		return ;
	new_node = new_ixmnode(data);
	if (!new_node)
		return ;
	new_node->xor_ptr = list->tail;
	if (list->tail)
		list->tail->xor_ptr = xor_func(list->tail->xor_ptr, new_node);
	else
		list->head = new_node;
	list->tail = new_node;
	++(list->len);
}

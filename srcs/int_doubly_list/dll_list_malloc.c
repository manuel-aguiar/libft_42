/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_list_malloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:45:10 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 18:45:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_dl_list.h"

t_idmnode *new_idmnode(int nbr)
{
    t_idmnode *new;

    new = malloc(sizeof(*new));
    if (!new)
        return (NULL);
    new->data = nbr;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

t_idmlist *new_idmlist(void)
{
    t_idmlist *list;

    list = malloc(sizeof(*list));
    if (!list)
        return (NULL);
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
    return (list);
}

void idmlist_in_head(t_idmlist* list, int data)
{
    t_idmnode* new_node;

    if (!list)
        return ;
    new_node = new_idmnode(data);
    if (!new_node)
        return ;
    if (list->head)
    {
        new_node->next = list->head;
        list->head->prev = new_node;
    }
    else
        list->tail = new_node;
    list->head = new_node;
    ++(list->len);
}

void idmlist_in_tail(t_idmlist* list, int data)
{
    t_idmnode* new_node;

    if (!list)
        return ;
    new_node = new_idmnode(data);
    if (!new_node)
        return ;
    if (list->tail)
    {
        new_node->prev = list->tail;
        list->tail->next = new_node;
    }
    else
        list->head = new_node;
    list->tail = new_node;
    ++(list->len);
}

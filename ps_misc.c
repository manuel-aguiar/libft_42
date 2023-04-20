/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_plays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:57:56 by marvin            #+#    #+#             */
/*   Updated: 2023/04/20 15:57:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void    calcminmax(t_icplist *list)
{
    t_icpnode *cur;

    if (list->len == 0)
    {
        list->min = -1;
        list->max = -1;
    }
    else
    {
        if (list->pivot->data > list->max)
            list->max = list->pivot->data;
        if (list->pivot->data < list->min)
            list->min = list->pivot->data;
        cur = list->pivot->next;
        while (cur != list->pivot)
        {
            if (list->pivot->data > list->max)
                list->max = list->pivot->data;
            if (list->pivot->data < list->min)
                list->min = list->pivot->data;
            cur = cur->next;
        }
    }
}

void minmax_newnode(t_icplist *list, int data)
{
    if (list->min == -1 || data < list->min)
        list->min = data;
    if (list->max == -1 || data > list->max)
        list->max = data;
}

/*
void    printmulti(char *str, int times)
{
    while (times--)
        printf("%s\n", str);
}*/


int rotatable(t_icplist *list)
{
    t_icpnode *node;
    int count;
    int new_pivot;

    if (list->len == 1)
        return (1);
    node = list->pivot;
    count = 0;
    while (node->next != list->pivot)
    {
        //printf("comparing cur %d with next %d, list->min %d, list->max %d\n", node->data, node->next->data, list->min, list->max);
        if (node->next->data == node->data + 1)
            count++;
        else if (node->next->data < node->data && node->data == list->max && node->next->data == list->min)
        {
            count++;
            new_pivot = count;
        }
        else
            return (0);
        node = node->next;
    }
    if (new_pivot > list->len / 2)
    {
        icplist_rotate(list, new_pivot - list->len);
        return (new_pivot - list->len);
    }
    else
    {
        icplist_rotate(list, new_pivot);
        return (new_pivot);
    }
}

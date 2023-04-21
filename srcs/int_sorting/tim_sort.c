/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tim_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:03:48 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 19:03:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_sorting.h"

static void	timsertsort(int *arr, int left, int right, int (*cmp)(int, int))
{
    int i;
    int temp;
    int j;

    i = left + 1;
    while (i <= right)
    {
        temp = arr[i];
        j = i - 1;
        while (j >= left && cmp(arr[j], temp))
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
        i++;
    }
}

static void	intersect(int *arr, int *copy, int *lmr, int (*cmp)(int, int))
{
    int len1;
    int len2;
    int i;
    int j;
    int k;

    len1 = lmr[1] - lmr[0] + 1;
    len2 = lmr[2] - lmr[1];
    ft_memcpy(copy, &arr[lmr[0]], (len1 + len2) * sizeof(*copy));
    i = 0;
    j = len1;
    k = lmr[0];
    while (i < len1 && j < (len1 + len2))
    {
        if (cmp(copy[j], copy[i]))
            arr[k++] = copy[i++];
        else
            arr[k++] = copy[j++];
    }
    if (i < len1)
        ft_memcpy(&arr[k], &copy[i], (len1 - i) * sizeof(*arr));
    if (j < (len1 + len2))
        ft_memcpy(&arr[k], &copy[j], ((len1 + len2) - j) * sizeof(*arr));

}

static void	tim_merge(int *arr, int *copy, int *lmr, int (*cmp)(int, int))
{
    int len1;
    int len2;
    int left;
    int middle;
    int right;

    left = lmr[0];
    middle = lmr[1];
    right = lmr[2];
    if (cmp(arr[middle + 1], arr[middle]))
        return ;
    if (cmp(arr[left], arr[right]))
    {

        len1 = middle - left + 1;
        len2 = right - middle;
        ft_memcpy(copy, &arr[left], len1 * sizeof(*copy));
        ft_memcpy(&arr[left], &arr[left + len1], len2 * sizeof(*copy));
        ft_memcpy(&arr[left + len2], copy, len1 * sizeof(*copy));
    }
    else
        intersect(arr, copy, lmr, cmp);
}

static int	helper_tern(int a, int b)
{
    if (a > b)
        return (b);
    return (a);
}

int			*tim_sort(int *arr, int n, int (*cmp)(int, int))
{
    int i;
    int size;
    int lmr[3];
    int *copy;

    i = 0;
    while (i < n)
    {
        timsertsort(arr, i, helper_tern((i + TIM_SORT_RUN - 1), (n - 1)), cmp);
        i += TIM_SORT_RUN;
    }
    if ((size = TIM_SORT_RUN) < n)
        copy = malloc(sizeof(*copy) * n);
    if (!copy)
        return (NULL);
    while (size < n)
    {
        lmr[0] = 0;
        while (lmr[0] < n)
        {
            lmr[1] = lmr[0] + size - 1;
            lmr[2] = helper_tern((lmr[0] + 2 * size - 1), (n - 1));
            if (lmr[1] < lmr[2])
                tim_merge(arr, copy, lmr, cmp);
            lmr[0] += 2 * size;
        }
        size *= 2;
    }
    free(copy);
    return (arr);
}

/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* normalize_index.c                                  :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/15 13:48:25 by anmakhov          #+#    #+#             */
/* Updated: 2026/06/15 21:44:55 by jdhamoda         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/*
** fill_array_from_stack - Copies values from the stack nodes into an array.
**
** @a:   Pointer to the stack.
** @arr: Pointer to the destination array.
*/
static void fill_array_from_stack(t_stack *a, int *arr)
{
    t_node  *curr;
    int     i;

    curr = a->top;
    i = 0;
    while (curr)
    {
        arr[i] = curr->value;
        curr = curr->next;
        i++;
    }
}

/*
** assign_indices_from_array - Maps sorted array positions to node indices.
**
** @a:   Pointer to the stack.
** @arr: Pointer to the sorted array of values.
**
** For each node in the stack, searches for its value in the sorted array
** to determine its relative rank (index).
*/
static void assign_indices_from_array(t_stack *a, int *arr)
{
    t_node  *curr;
    int     i;

    curr = a->top;
    while (curr)
    {
        i = 0;
        while (i < a->size)
        {
            if (curr->value == arr[i])
            {
                curr->index = i;
                break ;
            }
            i++;
        }
        curr = curr->next;
    }
}

/*
** normalize_index - Assigns relative indices to stack nodes based on 
** sorted order.
**
** @a: Pointer to the stack.
**
** Creates a copy of the stack values, sorts them using quicksort, and 
** assigns each node an index representing its position in the sorted 
** sequence. Frees allocated memory upon completion.
*/
void    normalize_index(t_stack *a)
{
    int *arr;

    if (!a || !a->top)
        return ;
    arr = malloc(sizeof(int) * a->size);
    if (!arr)
        return ;
    fill_array_from_stack(a, arr);
    quicksort(arr, 0, a->size - 1);
    assign_indices_from_array(a, arr);
    free(arr);
}
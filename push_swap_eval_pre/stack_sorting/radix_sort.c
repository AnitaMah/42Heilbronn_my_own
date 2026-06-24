/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* radix_sort.c                                       :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/02 12:07:04 by jdhamoda          #             */
/* Updated: 2026/06/15 15:19:15 by anmakhov         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/*
** handle_bit - Processes a specific bit for all elements in stack A.
** @a: The source stack.
** @b: The destination stack.
** @bit: The current bit position being processed.
** @apply: Configuration flags for operation execution.
**
** Iterates through stack A, pushing elements with a 0 at the current 
** bit position to stack B, or rotating stack A otherwise.
*/
static void handle_bit(t_stack *a, t_stack *b, int bit, t_flags *apply)
{
    int size;

    size = a->size;
    while (size > 0)
    {
        if (((a->top->index >> bit) & 1) == 0)
            pb(a, b, apply);
        else
            ra(a, apply);
        size--;
    }
}

/*
** get_max_bits - Determines the number of bits needed to represent the max index.
** @a: The stack containing the elements.
**
** Finds the maximum index in the stack and calculates the number 
** of bits required to represent it in binary.
*/
static int  get_max_bits(t_stack *a)
{
    int     max;
    int     bits;
    t_node  *cur;

    if (!a || !a->top)
        return (0);
    cur = a->top;
    max = cur->index;
    while (cur)
    {
        if (cur->index > max)
            max = cur->index;
        cur = cur->next;
    }
    bits = 0;
    while ((max >> bits) != 0)
        bits++;
    return (bits);
}

/*
** radix_sort - Sorts the stack using the Radix sort algorithm.
** @a: The source stack.
** @b: The temporary stack.
** @apply: Configuration flags for operation execution.
**
** Sorts the elements by iterating through each bit of the indices,
** partitioning elements between stacks A and B in multiple passes.
*/
void    radix_sort(t_stack *a, t_stack *b, t_flags *apply)
{
    int max_bits;
    int i;

    if (!a || !a->top)
        return ;
    max_bits = get_max_bits(a);
    i = 0;
    while (i < max_bits)
    {
        handle_bit(a, b, i, apply);
        while (b->top)
            pa(a, b, apply);
        i++;
    }
}
/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* chunk_sort.c                                       :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/02 12:07:09 by anmakhov          #+#             */
/* Updated: 2026/06/18 14:50:45 by anmakhov         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/*
** find_max - Searches for the node with the highest index in stack b.
** @b: The pointer to stack B.
**
** Iterates through the stack to find and return the node with the 
** maximum index value.
*/
t_node  *find_max(t_stack *b)
{
    t_node  *cur;
    t_node  *max;

    if (!b || !b->top)
        return (NULL);
    cur = b->top;
    max = b->top;
    while (cur)
    {
        if (cur->index > max->index)
            max = cur;
        cur = cur->next;
    }
    return (max);
}

/*
** init_chunks - Sets the chunk size based on the number of elements.
** @a: The pointer to stack A.
**
** Determines an appropriate chunk size (15 or 30) depending on the 
** input size for the sorting algorithm.
*/
static void init_chunks(t_stack *a)
{
    if (a->size <= 100)
        a->chunk_size = 15;
    else
        a->chunk_size = 30;
}

/*
** push_chunks - Moves elements from stack A to B in sorted chunks.
** @a: The source stack A.
** @b: The target stack B.
** @apply: Configuration flags for operation execution.
**
** Iteratively pushes elements into chunks based on their index. 
** Optimizes the movement using rotations.
*/
static void push_chunks(t_stack *a, t_stack *b, t_flags *apply)
{
    int max;
    int pushed;

    max = a->chunk_size;
    pushed = 0;
    while (a->size > 0)
    {
        if (a->top->index <= max)
        {
            pb(a, b, apply);
            if (b->top->index < max - (a->chunk_size / 2))
                rb(b, apply);
            pushed++;
            if (pushed == max)
                max += a->chunk_size;
        }
        else
        {
            if (find_position(a, max) <= a->size / 2)
                ra(a, apply);
            else
                rra(a, apply);
        }
    }
}

/*
** chunk_sort - Main function to sort the stack using the chunk algorithm.
** @a: The source stack.
** @b: The helper stack.
** @apply: Configuration flags for operation execution.
**
** Normalizes indices, initializes chunk parameters, and manages the 
** transfer of nodes between stacks to achieve sorting.
*/
void    chunk_sort(t_stack *a, t_stack *b, t_flags *apply)
{
    if (!a || a->size <= 1)
        return ;
    normalize_index(a);
    init_chunks(a);
    push_chunks(a, b, apply);
    restore_to_a(a, b, apply);
}
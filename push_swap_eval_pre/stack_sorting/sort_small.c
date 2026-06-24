/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* sort_small.c                                       :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/15 16:21:49 by anmakhov          #+#             */
/* Updated: 2026/06/18 14:53:52 by anmakhov         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/*
** sort_two - Sorts a stack of two elements in ascending order.
** @a: The pointer to stack A.
** @apply: Configuration flags for operation execution.
*/
void    sort_two(t_stack *a, t_flags *apply)
{
    if (a->top->value > a->top->next->value)
        sa(a, apply);
}

/*
** sort_three - Sorts a stack of three elements in ascending order.
** @a: The pointer to stack A.
** @apply: Configuration flags for operation execution.
**
** Uses a set of predefined conditions to sort the three elements
** with the minimum number of operations.
*/
void    sort_three(t_stack *a, t_flags *apply)
{
    int top;
    int mid;
    int bot;

    if (!a || !a->top || !a->top->next || !a->top->next->next)
        return ;
    top = a->top->value;
    mid = a->top->next->value;
    bot = a->top->next->next->value;
    if (top > mid && mid < bot && top < bot)
        sa(a, apply);
    else if (top > mid && mid > bot && top > bot)
    {
        sa(a, apply);
        rra(a, apply);
    }
    else if (top > mid && mid < bot && top > bot)
        ra(a, apply);
    else if (top < mid && mid > bot && top < bot)
    {
        sa(a, apply);
        ra(a, apply);
    }
    else if (top < mid && mid > bot && top > bot)
        rra(a, apply);
}

/*
** get_min_pos - Finds the index of the node with the minimum value.
** @stack: The pointer to the stack to search.
**
** Returns the zero-based position of the minimum element.
*/
static int  get_min_pos(t_stack *stack)
{
    t_node  *curr;
    int     min_val;
    int     min_pos;
    int     pos;

    curr = stack->top;
    min_val = curr->value;
    min_pos = 0;
    pos = 0;
    while (curr)
    {
        if (curr->value < min_val)
        {
            min_val = curr->value;
            min_pos = pos;
        }
        curr = curr->next;
        pos++;
    }
    return (min_pos);
}

/*
** get_stack_size - Calculates the current number of elements in the stack.
** @stack: The pointer to the stack.
*/
static int  get_stack_size(t_stack *stack)
{
    t_node  *curr;
    int     size;

    curr = stack->top;
    size = 0;
    while (curr)
    {
        size++;
        curr = curr->next;
    }
    return (size);
}

/*
** sort_four_five - Sorts a stack of four or five elements.
** @a: Stack A.
** @b: Stack B.
** @size: The current number of elements to sort.
** @apply: Configuration flags for operation execution.
**
** Extracts the minimum elements one by one into stack B, sorts the 
** remaining three in stack A, and pushes the elements back.
*/
void    sort_four_five(t_stack *a, t_stack *b, int size, t_flags *apply)
{
    int min_pos;
    int cur_size;

    while (size > 3)
    {
        min_pos = get_min_pos(a);
        cur_size = get_stack_size(a);
        if (min_pos <= cur_size / 2)
        {
            while (min_pos-- > 0)
                ra(a, apply);
        }
        else
        {
            while (min_pos++ < cur_size)
                rra(a, apply);
        }
        pb(a, b, apply);
        size--;
    }
    sort_three(a, apply);
    while (b->top)
        pa(a, b, apply);
}
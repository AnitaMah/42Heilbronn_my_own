/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* reverse.c                                          :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/01 14:17:00 by anmakhov          #+#             */
/* Updated: 2026/06/18 14:45:36 by anmakhov         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/*
** reverse_rotate_stack - Moves the bottom element of the stack to the top.
** @stack: The pointer to the stack structure to be rotated.
**
** Updates the pointers of the stack to shift the last element to the 
** head of the linked list. Does nothing if the stack has fewer than 2 elements.
*/
static void reverse_rotate_stack(t_stack *stack)
{
    t_node  *last;

    if (!stack || stack->size < 2)
        return ;
    last = stack->bottom;
    stack->bottom = last->prev;
    stack->bottom->next = NULL;
    last->prev = NULL;
    last->next = stack->top;
    stack->top->prev = last;
    stack->top = last;
}

/*
** rrr - Performs the 'reverse rotate a' and 'reverse rotate b' operations.
** @a: Stack A.
** @b: Stack B.
**
** Shifts both stacks down by one and prints "rrr".
*/
void    rrr(t_stack *a, t_stack *b)
{
    reverse_rotate_stack(a);
    reverse_rotate_stack(b);
    op_counter(OP_RRR);
    write(1, "rrr\n", 4);
}

/*
** rrb - Performs the 'reverse rotate b' operation.
** @b: Stack B.
**
** Shifts stack B down by one and prints "rrb".
*/
void    rrb(t_stack *b)
{
    reverse_rotate_stack(b);
    op_counter(OP_RRB);
    write(1, "rrb\n", 4);
}

/*
** rra - Performs the 'reverse rotate a' operation.
** @a: Stack A.
**
** Shifts stack A down by one and prints "rra".
*/
void    rra(t_stack *a)
{
    reverse_rotate_stack(a);
    op_counter(OP_RRA);
    write(1, "rra\n", 4);
}
/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* rotate.c                                           :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/01 22:00:12 by anmakhov          #+#    #+#             */
/* Updated: 2026/06/18 13:50:16 by anmakhov         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/*
** rotate_stack - Moves the top element of the stack to the bottom.
** @stack: The pointer to the stack structure to be rotated.
**
** Updates the pointers of the stack to shift the first element to the 
** tail of the linked list. Does nothing if the stack has fewer than 2 elements.
*/
static void rotate_stack(t_stack *stack)
{
    t_node  *first;

    if (!stack || stack->size < 2)
        return ;
    first = stack->top;
    stack->top = first->next;
    stack->top->prev = NULL;
    first->next = NULL;
    first->prev = stack->bottom;
    stack->bottom->next = first;
    stack->bottom = first;
}

/*
** rr - Performs the 'rotate a' and 'rotate b' operations simultaneously.
** @a: Stack A.
** @b: Stack B.
** @apply: Configuration flags for operation execution.
**
** Shifts both stacks up by one and prints "rr".
*/
void    rr(t_stack *a, t_stack *b, t_flags *apply)
{
    rotate_stack(a);
    rotate_stack(b);
    op_counter(OP_RR);
    if (!apply->count_only)
        write(1, "rr\n", 3);
}

/*
** rb - Performs the 'rotate b' operation.
** @b: Stack B.
** @apply: Configuration flags for operation execution.
**
** Shifts stack B up by one and prints "rb".
*/
void    rb(t_stack *b, t_flags *apply)
{
    rotate_stack(b);
    op_counter(OP_RB);
    if (!apply->count_only)
        write(1, "rb\n", 3);
}

/*
** ra - Performs the 'rotate a' operation.
** @a: Stack A.
** @apply: Configuration flags for operation execution.
**
** Shifts stack A up by one and prints "ra".
*/
void    ra(t_stack *a, t_flags *apply)
{
    rotate_stack(a);
    op_counter(OP_RA);
    if (!apply->count_only)
        write(1, "ra\n", 3);
}
/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* swap.c                                             :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/15 16:18:54 by anmakhov          #+#             */
/* Updated: 2026/06/18 13:50:26 by anmakhov         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/*
** swap_stack - Swaps the values and indices of the first two nodes in a stack.
** @stack: The pointer to the stack structure.
**
** Swaps the data (value and index) of the top node with the second node.
** Does nothing if the stack has fewer than 2 elements.
*/
static void swap_stack(t_stack *stack)
{
    int tmp_val;
    int tmp_idx;

    if (!stack || stack->size < 2)
        return ;
    tmp_val = stack->top->value;
    stack->top->value = stack->top->next->value;
    stack->top->next->value = tmp_val;
    tmp_idx = stack->top->index;
    stack->top->index = stack->top->next->index;
    stack->top->next->index = tmp_idx;
}

/*
** sa - Performs the 'swap a' operation.
** @a: Stack A.
** @apply: Configuration flags for operation execution.
**
** Swaps the first two elements of stack A and prints "sa".
*/
void    sa(t_stack *a, t_flags *apply)
{
    if (!a || a->size < 2)
        return ;
    swap_stack(a);
    op_counter(OP_SA);
    if (!apply->count_only)
        write(1, "sa\n", 3);
}

/*
** sb - Performs the 'swap b' operation.
** @b: Stack B.
** @apply: Configuration flags for operation execution.
**
** Swaps the first two elements of stack B and prints "sb".
*/
void    sb(t_stack *b, t_flags *apply)
{
    if (!b || b->size < 2)
        return ;
    swap_stack(b);
    op_counter(OP_SB);
    if (!apply->count_only)
        write(1, "sb\n", 3);
}

/*
** ss - Performs the 'swap a' and 'swap b' operations simultaneously.
** @a: Stack A.
** @b: Stack B.
** @apply: Configuration flags for operation execution.
**
** Swaps the first two elements of both stacks and prints "ss".
*/
void    ss(t_stack *a, t_stack *b, t_flags *apply)
{
    if ((!a || a->size < 2) || (!b || b->size < 2))
        return ;
    swap_stack(a);
    swap_stack(b);
    op_counter(OP_SS);
    if (!apply->count_only)
        write(1, "ss\n", 3);
}
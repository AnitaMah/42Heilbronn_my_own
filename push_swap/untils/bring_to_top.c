/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* bring_to_top.c                                     :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/15 16:19:09 by anmakhov          #+#             */
/* Updated: 2026/06/18 14:48:51 by anmakhov         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/*
** count_operations_to_top - Calculates the optimal number of rotations.
** @stack: The stack to search.
** @target: The node to bring to the top.
**
** Determines whether it is faster to rotate (positive) or reverse-rotate 
** (negative) to bring the target node to the top of the stack.
*/
static int  count_operations_to_top(t_stack *stack, t_node *target)
{
    t_node  *current;
    int     pos_from_top;
    int     pos_from_bottom;

    if (!stack || !target)
        return (0);
    pos_from_top = 0;
    current = stack->top;
    while (current && current != target)
    {
        pos_from_top++;
        current = current->next;
    }
    if (!current)
        return (0);
    pos_from_bottom = stack->size - pos_from_top;
    if (pos_from_top <= pos_from_bottom)
        return (pos_from_top);
    return (-pos_from_bottom);
}

/*
** execute_rotation - Performs the calculated number of rotations.
** @stack: The stack to rotate.
** @ops: Number of rotations (positive for ra/rb, negative for rra/rrb).
*/
void    execute_rotation(t_stack *stack, int ops)
{
    while (ops != 0)
    {
        if (ops > 0)
        {
            if (stack->name == 'a')
                ra(stack);
            else
                rb(stack);
            ops--;
        }
        else
        {
            if (stack->name == 'a')
                rra(stack);
            else
                rrb(stack);
            ops++;
        }
    }
}

/*
** bring_to_top - Brings a specific node to the top of the stack.
** @stack: The stack containing the node.
** @target: The target node to bring to the top.
**
** Finds the optimal path to the top and executes the necessary rotations.
*/
void    bring_to_top(t_stack *stack, t_node *target)
{
    int ops;

    if (!stack || !target)
        return ;
    ops = count_operations_to_top(stack, target);
    execute_rotation(stack, ops);
}
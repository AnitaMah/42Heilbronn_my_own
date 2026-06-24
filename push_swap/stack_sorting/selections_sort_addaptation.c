/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* selections_sort_addaptation.c                      :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/01 22:01:14 by anmakhov          #+#             */
/* Updated: 2026/06/18 14:52:43 by anmakhov         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/*
** find_min_node - Finds the node with the minimum value in the stack.
** @a: The pointer to stack A.
**
** Iterates through the entire stack to identify and return the node 
** containing the smallest integer value.
*/
t_node  *find_min_node(t_stack *a)
{
    t_node  *min;
    t_node  *current;

    if (!a || !a->top)
        return (NULL);
    current = a->top;
    min = a->top;
    while (current)
    {
        if (current->value < min->value)
            min = current;
        current = current->next;
    }
    return (min);
}

/*
** selection_sort_adaptation - Sorts the stack using a selection sort approach.
** @a: The source stack A.
** @b: The target stack B.
** @apply: Configuration flags for operation execution.
**
** Repeatedly finds the minimum element in stack A, moves it to the top 
** using rotations, and pushes it to stack B. Finally, returns all 
** elements to stack A in sorted order.
*/
void    selection_sort_adaptation(t_stack *a, t_stack *b)
{
    t_node  *min;

    while (a->size > 0)
    {
        min = find_min_node(a);
        if (!min)
            return ;
        bring_to_top(a, min);
        pb(a, b);
    }
    restore_to_a(a, b);
}
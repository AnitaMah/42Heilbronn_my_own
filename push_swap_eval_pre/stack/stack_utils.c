/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* stack_utils.c                                      :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/15 11:14:22 by jdhamoda          #+#    #+#             */
/* Updated: 2026/06/15 21:30:53 by jdhamoda         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/*
** find_position - Finds the position of the first node meeting an index condition.
** @stack: The pointer to the stack structure to search in.
** @index_limit: The maximum index value to look for.
**
** Iterates through the stack from top to bottom. Returns the zero-based 
** position of the first node whose index is less than or equal to 
** the provided index_limit.
*/
int find_position(t_stack *stack, int index_limit)
{
    t_node  *cur;
    int     pos;

    cur = stack->top;
    pos = 0;
    while (cur)
    {
        if (cur->index <= index_limit)
            return (pos);
        pos++;
        cur = cur->next;
    }
    return (pos);
}
/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* is_sorted.c                                        :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/11 13:26:04 by anmakhov          #+#    #+#             */
/* Updated: 2026/06/15 15:05:51 by jdhamoda         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/*
** is_sorted - Checks if the stack is sorted in ascending order.
**
** @a: Pointer to the stack structure.
**
** Iterates through the stack starting from the top node. If any element is
** greater than the next element, the stack is not sorted.
** Returns 1 if the stack is sorted or empty/null, otherwise returns 0.
*/
int is_sorted(t_stack *a)
{
    t_node  *cur;

    if (!a || !a->top)
        return (1);
    cur = a->top;
    while (cur->next)
    {
        if (cur->value > cur->next->value)
            return (0);
        cur = cur->next;
    }
    return (1);
}
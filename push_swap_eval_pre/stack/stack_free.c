/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* stack_free.c                                       :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/15 11:14:39 by jdhamoda          #+#    #+#             */
/* Updated: 2026/06/15 15:05:00 by jdhamoda         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/*
** free_stack - Frees all nodes in the stack and resets stack parameters.
** @a: The pointer to the stack structure to be freed.
**
** Iterates through the linked list of nodes, freeing each one.
** Resets the stack's top, bottom, size, and chunk_size to clear the structure.
*/
void    free_stack(t_stack *a)
{
    t_node  *cur;
    t_node  *next;

    if (!a)
        return ;
    cur = a->top;
    while (cur)
    {
        next = cur->next;
        free(cur);
        cur = next;
    }
    a->top = NULL;
    a->bottom = NULL;
    a->size = 0;
    a->chunk_size = 0;
}
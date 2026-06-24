/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* stack_init.c                                       :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/01 14:11:35 by jdhamoda          #+#    #+#             */
/* Updated: 2026/06/15 15:04:55 by jdhamoda         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/*
** init_stack - Initializes a stack structure with default values.
** @stack: The pointer to the stack structure to be initialized.
** @name: The identifier name for the stack (e.g., 'a' or 'b').
**
** Sets the stack's pointers (top, bottom) to NULL and initializes 
** size and chunk_size to 0.
*/
void    init_stack(t_stack *stack, char name)
{
    if (!stack)
        return ;
    stack->top = NULL;
    stack->bottom = NULL;
    stack->size = 0;
    stack->chunk_size = 0;
    stack->name = name;
}
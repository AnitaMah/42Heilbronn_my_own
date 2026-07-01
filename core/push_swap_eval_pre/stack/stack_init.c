/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 14:11:35 by jdhamoda          #+#    #+#             */
/*   Updated: 2026/06/26 13:08:46 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * @brief Initializes a new stack structure with default values.
 * @param stack The pointer to the stack structure to initialize.
 * @param name The character identifier assigned to the stack (e.g.,
	'a' or 'b').
 */

void	init_stack(t_stack *stack, char name)
{
	if (!stack)
		return ;
	stack->top = NULL;
	stack->bottom = NULL;
	stack->size = 0;
	stack->chunk_size = 0;
	stack->name = name;
}

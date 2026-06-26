/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 22:00:12 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/26 12:56:19 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * @brief Rotates the stack upwards by shifting the top element to the bottom.
 * @param stack The stack to be rotated.
 */

static void	rotate_stack(t_stack *stack)
{
	t_node	*first;

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

/**
 * @brief Performs rotate on both stack A and stack B.
 * @param a Stack A to be rotated.
 * @param b Stack B to be rotated.
 */

void	rr(t_stack *a, t_stack *b)
{
	rotate_stack(a);
	rotate_stack(b);
	op_counter(OP_RR);
	write(1, "rr\n", 3);
}

/**
 * @brief Performs rotate on stack B.
 * @param b The stack to be rotated.
 */

void	rb(t_stack *b)
{
	rotate_stack(b);
	op_counter(OP_RB);
	write(1, "rb\n", 3);
}

/**
 * @brief Performs rotate on stack A.
 * @param a The stack to be rotated.
 */

void	ra(t_stack *a)
{
	rotate_stack(a);
	op_counter(OP_RA);
	write(1, "ra\n", 3);
}

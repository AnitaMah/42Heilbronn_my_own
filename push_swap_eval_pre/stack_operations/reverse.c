/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 14:17:00 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/26 12:55:18 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * @brief Rotates the stack downwards by shifting the bottom element to the top.
 * @param stack The stack to perform the reverse rotation on.
 */

static void	reverse_rotate_stack(t_stack *stack)
{
	t_node	*last;

	if (!stack || stack->size < 2)
		return ;
	last = stack->bottom;
	stack->bottom = last->prev;
	stack->bottom->next = NULL;
	last->prev = NULL;
	last->next = stack->top;
	stack->top->prev = last;
	stack->top = last;
}

/**
 * @brief Performs reverse rotate on both stack A and stack B.
 * @param a Stack A to be reverse rotated.
 * @param b Stack B to be reverse rotated.
 */

void	rrr(t_stack *a, t_stack *b)
{
	reverse_rotate_stack(a);
	reverse_rotate_stack(b);
	op_counter(OP_RRR);
	write(1, "rrr\n", 4);
}

/**
 * @brief Performs reverse rotate on stack B.
 * @param b The stack to be reverse rotated.
 */

void	rrb(t_stack *b)
{
	reverse_rotate_stack(b);
	op_counter(OP_RRB);
	write(1, "rrb\n", 4);
}

/**
 * @brief Performs reverse rotate on stack A.
 * @param a The stack to be reverse rotated.
 */

void	rra(t_stack *a)
{
	reverse_rotate_stack(a);
	op_counter(OP_RRA);
	write(1, "rra\n", 4);
}

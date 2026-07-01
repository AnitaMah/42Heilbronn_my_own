/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 22:00:12 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/17 12:11:53 by jdhamoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

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

void	rr(t_stack *a, t_stack *b)
{
	rotate_stack(a);
	rotate_stack(b);
	op_counter(OP_RR);
	write(1, "rr\n", 3);
}

void	rb(t_stack *b)
{
	rotate_stack(b);
	op_counter(OP_RB);
	write(1, "rb\n", 3);
}

void	ra(t_stack *a)
{
	rotate_stack(a);
	op_counter(OP_RA);
	write(1, "ra\n", 3);
}

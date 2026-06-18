/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 14:17:00 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/18 14:45:36 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

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

void	rrr(t_stack *a, t_stack *b, t_flags *apply)
{
	reverse_rotate_stack(a);
	reverse_rotate_stack(b);
	op_counter(OP_RRR);
	if (!apply->count_only)
		write(1, "rrr\n", 4);
}

void	rrb(t_stack *b, t_flags *apply)
{
	reverse_rotate_stack(b);
	op_counter(OP_RRB);
	if (!apply->count_only)
		write(1, "rrb\n", 4);
}

void	rra(t_stack *a, t_flags *apply)
{
	reverse_rotate_stack(a);
	op_counter(OP_RRA);
	if (!apply->count_only)
		write(1, "rra\n", 4);
}

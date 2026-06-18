/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:18:54 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/17 11:12:58 by jdhamoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

static void	swap_stack(t_stack *stack)
{
	int	tmp_val;
	int	tmp_idx;

	if (!stack || stack->size < 2)
		return ;
	tmp_val = stack->top->value;
	stack->top->value = stack->top->next->value;
	stack->top->next->value = tmp_val;
	tmp_idx = stack->top->index;
	stack->top->index = stack->top->next->index;
	stack->top->next->index = tmp_idx;
}

void	sa(t_stack *a)
{
	if (!a || a->size < 2)
		return ;
	swap_stack(a);
	op_counter(OP_SA);
	write(1, "sa\n", 3);
}

void	sb(t_stack *b)
{
	if (!b || b->size < 2)
		return ;
	swap_stack(b);
	op_counter(OP_SB);
	write(1, "sb\n", 3);
}

void	ss(t_stack *a, t_stack *b)
{
	if ((!a || a->size < 2) || (!b || b->size < 2))
		return ;
	swap_stack(a);
	swap_stack(b);
	op_counter(OP_SS);
	write(1, "ss\n", 3);
}

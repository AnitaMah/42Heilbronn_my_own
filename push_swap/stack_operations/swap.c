/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 14:17:00 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/01 14:17:01 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ss(t_stack *a, t_stack *b)
{
	swap_stack(a);
	swap_stack(b);
	write(1, "ss\n", 3);
}

void	sb(t_stack *b)
{
	swap_stack(b);
	write(1, "sb\n", 3);
}

void	sa(t_stack *a)
{
	swap_stack(a);
	write(1, "sa\n", 3);
}

static void	swap_stack(t_stack *stack)
{
	int	tmp;

	if (!stack || stack->size < 2)
		return ;
	tmp = stack->top->value;
	stack->top->value = stack->top->next->value;
	stack->top->next->value = tmp;
}

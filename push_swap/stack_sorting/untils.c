/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   untils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 16:32:43 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/01 16:56:47 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	bring_to_top(t_stack *stack, t_node *target)
{
	int		pos;
	int		size;
	t_node	*current;

	if (!stack || !stack->top || !target)
		return ;
	pos = 0;
	size = stack->size;
	current = stack->top;
	while (current && current != target)
	{
		current = current->next;
		pos++;
	}
	if (!current)
		return ;
	if (pos <= size / 2)
		while (stack->top != target)
			rb(stack);
	else
		while (stack->top != target)
			rrb(stack);
}

void	restore_to_a(t_stack *a, t_stack *b)
{
	while (b->size > 0)
	{
		pa(a, b);
	}
}

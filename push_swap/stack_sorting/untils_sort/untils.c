/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   untils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anita <anita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 16:32:43 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/03 10:54:59 by anita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

t_node	*find_max(t_stack *b)
{
	t_node	*current;
	t_node	*max;

	if (!b || !b->top)
		return (NULL);
	current = b->top;
	max = b->top;
	while (current)
	{
		if (current->index > max->index)
			max = current;
		current = current->next;
	}
	return (max);
}

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
	t_node	*max;

	while (b->size > 0)
	{
		max = find_max(b);
		bring_to_top(b, max);
		pa(a, b);
	}
}

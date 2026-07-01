/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bring_to_top.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:19:09 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/15 21:22:10 by jdhamoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

static int	count_operations_to_top(t_stack *stack, t_node *target)
{
	t_node	*current;
	int		pos_from_top;
	int		pos_from_bottom;

	if (!stack || !target)
		return (0);
	pos_from_top = 0;
	current = stack->top;
	while (current && current != target)
	{
		pos_from_top++;
		current = current->next;
	}
	if (!current)
		return (0);
	pos_from_bottom = stack->size - pos_from_top;
	if (pos_from_top <= pos_from_bottom)
		return (pos_from_top);
	return (-pos_from_bottom);
}

void	execute_rotation(t_stack *stack, int ops)
{
	while (ops != 0)
	{
		if (ops > 0)
		{
			if (stack->name == 'a')
				ra(stack);
			else
				rb(stack);
			ops--;
		}
		else
		{
			if (stack->name == 'a')
				rra(stack);
			else
				rrb(stack);
			ops++;
		}
	}
}

void	bring_to_top(t_stack *stack, t_node *target)
{
	int	ops;

	if (!stack || !target)
		return ;
	ops = count_operations_to_top(stack, target);
	execute_rotation(stack, ops);
}

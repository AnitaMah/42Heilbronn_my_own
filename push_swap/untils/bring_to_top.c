/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bring_to_top.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:19:09 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/18 14:48:51 by anmakhov         ###   ########.fr       */
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

void	execute_rotation(t_stack *stack, int ops, t_flags *apply)
{
	while (ops != 0)
	{
		if (ops > 0)
		{
			if (stack->name == 'a')
				ra(stack, apply);
			else
				rb(stack, apply);
			ops--;
		}
		else
		{
			if (stack->name == 'a')
				rra(stack, apply);
			else
				rrb(stack, apply);
			ops++;
		}
	}
}

void	bring_to_top(t_stack *stack, t_node *target, t_flags *apply)
{
	int	ops;

	if (!stack || !target)
		return ;
	ops = count_operations_to_top(stack, target);
	execute_rotation(stack, ops, apply);
}

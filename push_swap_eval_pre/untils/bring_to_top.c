/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bring_to_top.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:19:09 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/26 12:36:26 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * Calculates shortest rotations needed to move target to stack top.
 * Returns positive for rotations (ra/rb) or negative for reverse (rra/rrb).
 * @param stack Pointer to the stack structure.
 * @param target Pointer to the node intended for the top.
 * @return Integer representing number and direction of operations.
 */

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
/**
 * Executes the calculated stack rotation operations iteratively.
 * Performs either standard rotations or reverse rotations based on sign.
 * @param stack Pointer to the stack structure being manipulated.
 * @param ops Signed integer indicating operation count and type.
 */

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

/**
 * Moves a specific node to the top position of the stack.
 * Determines the optimal path and triggers rotation execution.
 * @param stack Pointer to the stack structure.
 * @param target Pointer to the node to be moved to the top.
 */

void	bring_to_top(t_stack *stack, t_node *target)
{
	int	ops;

	if (!stack || !target)
		return ;
	ops = count_operations_to_top(stack, target);
	execute_rotation(stack, ops);
}

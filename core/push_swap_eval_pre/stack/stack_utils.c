/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 11:14:22 by jdhamoda          #+#    #+#             */
/*   Updated: 2026/06/26 13:46:35 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * @brief Finds the position of the first node with an index below or equal to
 * the limit.
 * @param stack The stack to search through.
 * @param index_limit The threshold index to compare against nodes.
 * @return The position of the found node, or the final position if not found.
 */

int	find_position(t_stack *stack, int index_limit)
{
	t_node	*cur;
	int		pos;

	cur = stack->top;
	pos = 0;
	while (cur)
	{
		if (cur->index <= index_limit)
			return (pos);
		pos++;
		cur = cur->next;
	}
	return (pos);
}

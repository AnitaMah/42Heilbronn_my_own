/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_to_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:06:30 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/26 12:43:14 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * Moves all elements from stack B back to stack A in descending order.
 * Finds the maximum value in B, brings it to the top, and pushes to A.
 * @param a Pointer to stack A structure.
 * @param b Pointer to stack B structure.
 */

void	restore_to_a(t_stack *a, t_stack *b)
{
	t_node	*max;

	while (b->size > 0)
	{
		max = find_max(b);
		if (!max)
			break ;
		if (b->top != max)
			bring_to_top(b, max);
		pa(a, b);
	}
}

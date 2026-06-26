/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selections_sort_addaptation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 22:01:14 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/26 12:50:42 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * @brief Finds the node with the minimum value in stack A.
 * - Traverses the stack to identify the node containing the smallest integer.
 * - @param a Pointer to the stack structure to search.
 * - @return Pointer to the node with the minimum value, or NULL if empty.
 */

t_node	*find_min_node(t_stack *a)
{
	t_node	*min;
	t_node	*current;

	if (!a || !a->top)
		return (NULL);
	current = a->top;
	min = a->top;
	while (current)
	{
		if (current->value < min->value)
			min = current;
		current = current->next;
	}
	return (min);
}

/**
 * @brief Sorts the stack using a selection-based adaptation algorithm.
 * - Iteratively finds the minimum, brings it to the top, and pushes to stack B.
 * - @param a Pointer to stack A, @param b Pointer to stack B.
 */

void	selection_sort_adaptation(t_stack *a, t_stack *b)
{
	t_node	*min;

	normalize_index(a);
	while (a->size > 0)
	{
		min = find_min_node(a);
		if (!min)
			return ;
		bring_to_top(a, min);
		pb(a, b);
	}
	restore_to_a(a, b);
}

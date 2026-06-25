/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selections_sort_addaptation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 22:01:14 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/15 21:58:51 by jdhamoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

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

void	selection_sort_adaptation(t_stack *a, t_stack *b)
{
	t_node	*min;

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

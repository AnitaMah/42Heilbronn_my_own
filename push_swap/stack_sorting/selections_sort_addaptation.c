/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selections_sort_addaptation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 22:01:14 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/18 14:52:43 by anmakhov         ###   ########.fr       */
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

void	selection_sort_adaptation(t_stack *a, t_stack *b, t_flags *apply)
{
	t_node	*min;

	while (a->size > 0)
	{
		min = find_min_node(a);
		if (!min)
			return ;
		bring_to_top(a, min, apply);
		pb(a, b, apply);
	}
	restore_to_a(a, b, apply);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:07:09 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/18 14:50:45 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

t_node	*find_max(t_stack *b)
{
	t_node	*cur;
	t_node	*max;

	if (!b || !b->top)
		return (NULL);
	cur = b->top;
	max = b->top;
	while (cur)
	{
		if (cur->index > max->index)
			max = cur;
		cur = cur->next;
	}
	return (max);
}

static void	init_chunks(t_stack *a)
{
	if (a->size <= 100)
		a->chunk_size = 15;
	else
		a->chunk_size = 30;
}

static void	push_chunks(t_stack *a, t_stack *b, t_flags *apply)
{
	int	max;
	int	pushed;

	max = a->chunk_size;
	pushed = 0;
	while (a->size > 0)
	{
		if (a->top->index <= max)
		{
			pb(a, b, apply);
			if (b->top->index < max - (a->chunk_size / 2))
				rb(b, apply);
			pushed++;
			if (pushed == max)
				max += a->chunk_size;
		}
		else
		{
			if (find_position(a, max) <= a->size / 2)
				ra(a, apply);
			else
				rra(a, apply);
		}
	}
}

void	chunk_sort(t_stack *a, t_stack *b, t_flags *apply)
{
	if (!a || a->size <= 1)
		return ;
	normalize_index(a);
	init_chunks(a);
	push_chunks(a, b, apply);
	restore_to_a(a, b, apply);
}

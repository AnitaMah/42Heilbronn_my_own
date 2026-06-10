/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anita <anita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:07:09 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/03 08:39:33 by anita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	push_chunks(t_stack *a, t_stack *b)
{
	int	max;
	int	pushed;

	pushed = 0;
	max = a->chunk_size;
	while (a->size > 0)
	{
		if (a->top->index <= max)
		{
			pb(a, b);
			pushed++;
		}
		else
			ra(a);
		if (pushed == a->chunk_size)
		{
			max += a->chunk_size;
			pushed = 0;
		}
	}
}

void	init_chunks(t_stack *a)
{
	a->chunk_size = a->size / 5;
	if (a->chunk_size < 1)
		a->chunk_size = 1;
}

void	chunk_sort(t_stack *a, t_stack *b)
{
	normalize_index(a);
	init_chunks(a);
	push_chunks(a, b);
	restore_to_a(a, b);
}

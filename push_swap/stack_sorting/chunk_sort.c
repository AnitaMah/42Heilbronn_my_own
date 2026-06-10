/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:07:09 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/10 17:32:44 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"
#include <stdio.h>

void	push_chunks(t_stack *a, t_stack *b)
{
	int	max;
	int	pushed;

	pushed = 0;
	max = a->chunk_size;
	while (a->size > 0)
	{
		fprintf(stderr, "DEBUG: a->top->index=%d, max=%d, pushed=%d,a->size=%d\n", a->top->index, max, pushed, a->size);
		if (a->top->index <= max)
		{
			pb(a, b);
			pushed++;
			fprintf(stderr, "  -> Pushed (pushed now=%d)\n", pushed);
		}
		else
		{
			ra(a);
			fprintf(stderr, "  -> Rotated\n");
		}
		if (pushed == a->chunk_size)
		{
			fprintf(stderr, "  -> Chunk complete, moving to next chunk\n");
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
	fprintf(stderr, "DEBUG: init_chunks - size=%d, chunk_size=%d\n", a->size,
		a->chunk_size);
}

void	chunk_sort(t_stack *a, t_stack *b)
{
	normalize_index(a);
	init_chunks(a);
	push_chunks(a, b);
	restore_to_a(a, b);
}

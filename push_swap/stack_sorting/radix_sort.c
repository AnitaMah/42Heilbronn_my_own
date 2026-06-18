/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:07:04 by jdhamoda          #+#             */
/*   Updated: 2026/06/15 15:19:15 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

static void	handle_bit(t_stack *a, t_stack *b, int bit)
{
	int	size;

	size = a->size;
	while (size > 0)
	{
		if (((a->top->index >> bit) & 1) == 0)
			pb(a, b);
		else
			ra(a);
		size--;
	}
}

static int	get_max_bits(t_stack *a)
{
	int		max;
	int		bits;
	t_node	*cur;

	if (!a || !a->top)
		return (0);
	cur = a->top;
	max = cur->index;
	while (cur)
	{
		if (cur->index > max)
			max = cur->index;
		cur = cur->next;
	}
	bits = 0;
	while ((max >> bits) != 0)
		bits++;
	return (bits);
}

void	radix_sort(t_stack *a, t_stack *b)
{
	int	max_bits;
	int	i;

	if (!a || !a->top)
		return ;
	max_bits = get_max_bits(a);
	i = 0;
	while (i < max_bits)
	{
		handle_bit(a, b, i);
		while (b->top)
			pa(a, b);
		i++;
	}
}

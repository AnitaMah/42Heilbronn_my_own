/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 13:48:25 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/27 16:05:57 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

static void	fill_array_from_stack(t_stack *a, int *arr)
{
	t_node	*curr;
	int		i;

	curr = a->top;
	i = 0;
	while (curr)
	{
		arr[i] = curr->value;
		curr = curr->next;
		i++;
	}
}

static void	assign_indices_from_array(t_stack *a, int *arr)
{
	t_node	*curr;
	int		i;

	curr = a->top;
	while (curr)
	{
		i = 0;
		while (i < a->size)
		{
			if (curr->value == arr[i])
			{
				curr->index = i;
				break ;
			}
			i++;
		}
		curr = curr->next;
	}
}

void	normalize_index(t_stack *a)
{
	int	*arr;

	if (!a || !a->top)
		return ;
	arr = malloc(sizeof(int) * a->size);
	if (!arr)
		return ;
	fill_array_from_stack(a, arr);
	quicksort(arr, 0, a->size - 1);
	assign_indices_from_array(a, arr);
	free(arr);
}

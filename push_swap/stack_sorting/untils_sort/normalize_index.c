/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:07:19 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/02 12:07:19 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	assign_index(t_stack *a, int *arr)
{
	t_node	*current;
	int		iter;

	current = a->top;
	while (current)
	{
		iter = 0;
		while (iter < a->size)
		{
			if (current->value == arr[iter])
			{
				current->index = iter;
				break ;
			}
			iter++;
		}
		current = current->next;
	}
}

int	*stack_to_array(t_stack *a)
{
	int		*arr;
	int		pos;
	t_node	*current;

	arr = malloc(sizeof(int) * a->size);
	if (!arr)
		return ;
	pos = 0;
	current = a->top;
	while (current)
	{
		arr[pos] = current->value;
		pos++;
		current = current->next;
	}
	return (arr);
}

void	normalize_index(t_stack *a)
{
	int		*arr;
	int		pos;
	t_node	*current;

	arr = stack_to_array(a);
	if (!arr)
		return ;
	quicksort(arr, 0, a->size - 1);
	assign_index(a, arr);
	free(arr);
}

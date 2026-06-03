/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anita <anita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:07:19 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/03                          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

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

	if (!a || a->size <= 0)
		return (NULL);
	arr = malloc(sizeof(int) * a->size);
	if (!arr)
		return (NULL);
	pos = 0;
	current = a->top;
	while (current)
	{
		arr[pos++] = current->value;
		current = current->next;
	}
	return (arr);
}

void	normalize_index(t_stack *a)
{
	int		*arr;

	if (!a || !a->top)
		return ;
	arr = stack_to_array(a);
	if (!arr)
		return ;
	quicksort(arr, 0, a->size - 1);
	assign_index(a, arr);
	free(arr);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 13:48:25 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/26 13:23:32 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * @brief Copies all stack node values into a flat integer array.
 * @param a The source stack, arr The destination array.
 */

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

/**
 * @brief Maps sorted array positions to node index fields.
 * @param a The stack to index, arr The sorted source array.
 */

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

/**
 * @brief Normalizes stack values to indices based on sorted order.
 * @param a Pointer to the stack to be indexed.
 */

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

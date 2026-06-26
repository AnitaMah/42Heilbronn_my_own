/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_from_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 11:59:30 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/26 13:23:47 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * @brief Initializes the stack by creating nodes from an integer array.
 * @param a Target stack, arr Source array, size Number of elements.
 * @return 1 on success, 0 if memory allocation fails.
 */

int	stack_from_array(t_stack *a, int *arr, int size)
{
	int		i;
	t_node	*new;

	i = 0;
	while (i < size)
	{
		new = malloc(sizeof(t_node));
		if (!new)
			return (0);
		new->value = arr[i];
		new->index = 0;
		new->next = NULL;
		new->prev = a->bottom;
		if (!a->top)
			a->top = new;
		else
			a->bottom->next = new;
		a->bottom = new;
		a->size++;
		i++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:07:09 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/26 12:45:51 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * @brief Finds the node with the maximum index in stack B.
 * - Traverses the stack to identify the node with the highest index.
 * - @param b Pointer to the stack structure to search.
 * - @return Pointer to the node with the max index, or NULL if empty.
 */

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

/**
 * @brief Initializes chunk sizes based on the stack's total size.
 * - Sets chunk boundaries to optimize the sorting process for 100/500 inputs.
 * - @param a Pointer to stack A used to determine the sizing strategy.
 */

static void	init_chunks(t_stack *a)
{
	if (a->size <= 100)
		a->chunk_size = 15;
	else
		a->chunk_size = 30;
}

/**
 * @brief Pushes elements from stack A to B based on defined chunks.
 * - Iterates through elements,
	rotating stack A until the target index is found.
 * - @param a Pointer to stack A.
 * - @param b Pointer to stack B.
 */

static void	push_chunks(t_stack *a, t_stack *b)
{
	int	max;
	int	pushed;

	max = a->chunk_size;
	pushed = 0;
	while (a->size > 0)
	{
		if (a->top->index <= max)
		{
			pb(a, b);
			if (b->top->index < max - (a->chunk_size / 2))
				rb(b);
			pushed++;
			if (pushed == max)
				max += a->chunk_size;
		}
		else
		{
			if (find_position(a, max) <= a->size / 2)
				ra(a);
			else
				rra(a);
		}
	}
}

/**
 * @brief Main function to perform chunk-based sorting of the stack.
 * - Normalizes indices, initializes chunks, pushes to B, then restores.
 * - @param a Pointer to stack A.
 * - @param b Pointer to stack B.
 */

void	chunk_sort(t_stack *a, t_stack *b)
{
	if (!a || a->size <= 1)
		return ;
	normalize_index(a);
	init_chunks(a);
	push_chunks(a, b);
	restore_to_a(a, b);
}

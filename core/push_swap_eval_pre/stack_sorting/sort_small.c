/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:21:49 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/26 12:52:43 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * @brief Sorts the stack if it contains only two elements.
 * - Swaps the top two elements if they are not in ascending order.
 * - @param a Pointer to stack A to be sorted.
 */

void	sort_two(t_stack *a)
{
	if (a->top->value > a->top->next->value)
		sa(a);
}

/**
 * @brief Sorts a stack of exactly three elements.
 * - Determines the permutation and applies necessary rotations or swaps.
 * - @param a Pointer to stack A to be sorted.
 */

void	sort_three(t_stack *a)
{
	int	top;
	int	mid;
	int	bot;

	if (!a || !a->top || !a->top->next || !a->top->next->next)
		return ;
	top = a->top->value;
	mid = a->top->next->value;
	bot = a->top->next->next->value;
	if (top > mid && mid < bot && top < bot)
		sa(a);
	else if (top > mid && mid > bot && top > bot)
	{
		sa(a);
		rra(a);
	}
	else if (top > mid && mid < bot && top > bot)
		ra(a);
	else if (top < mid && mid > bot && top < bot)
	{
		sa(a);
		ra(a);
	}
	else if (top < mid && mid > bot && top > bot)
		rra(a);
}

/**
 * @brief Finds the position of the minimum value in the stack.
 * - Iterates through the stack to identify the index of the smallest node.
 * - @param stack Pointer to the stack to be analyzed.
 * - @return The index position of the minimum value.
 */

static int	get_min_pos(t_stack *stack)
{
	t_node	*curr;
	int		min_val;
	int		min_pos;
	int		pos;

	curr = stack->top;
	min_val = curr->value;
	min_pos = 0;
	pos = 0;
	while (curr)
	{
		if (curr->value < min_val)
		{
			min_val = curr->value;
			min_pos = pos;
		}
		curr = curr->next;
		pos++;
	}
	return (min_pos);
}

/**
 * @brief Calculates the current number of elements in the stack.
 * - Traverses the linked list to count the total nodes present.
 * - @param stack Pointer to the stack.
 * - @return Total number of elements in the stack.
 */

static int	get_stack_size(t_stack *stack)
{
	t_node	*curr;
	int		size;

	curr = stack->top;
	size = 0;
	while (curr)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

/**
 * @brief Manages sorting for stacks of four or five elements.
 * - Pushes minimum elements to stack B until only three remain, then sorts.
 * - @param a Pointer to stack A, @param b Pointer to stack B,
	@param size Current size.
 */

void	sort_four_five(t_stack *a, t_stack *b, int size)
{
	int	min_pos;
	int	cur_size;

	while (size > 3)
	{
		min_pos = get_min_pos(a);
		cur_size = get_stack_size(a);
		if (min_pos <= cur_size / 2)
		{
			while (min_pos-- > 0)
				ra(a);
		}
		else
		{
			while (min_pos++ < cur_size)
				rra(a);
		}
		pb(a, b);
		size--;
	}
	sort_three(a);
	while (b->top)
		pa(a, b);
}

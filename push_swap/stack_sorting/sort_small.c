/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:21:49 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/15 16:21:56 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

void	sort_two(t_stack *a)
{
	if (a->top->value > a->top->next->value)
		sa(a);
}

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

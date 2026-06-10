/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   untils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anita <anita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 16:32:43 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/03 10:54:59 by anita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

static void	rotate_stack_silent(t_stack *stack)
{
	t_node	*first;

	if (!stack || stack->size < 2)
		return ;
	first = stack->top;
	stack->top = first->next;
	stack->top->prev = NULL;
	first->next = NULL;
	first->prev = stack->bottom;
	stack->bottom->next = first;
	stack->bottom = first;
}

static void	reverse_rotate_stack_silent(t_stack *stack)
{
	t_node	*last;

	if (!stack || stack->size < 2)
		return ;
	last = stack->bottom;
	stack->bottom = last->prev;
	stack->bottom->next = NULL;
	last->prev = NULL;
	last->next = stack->top;
	stack->top->prev = last;
	stack->top = last;
}

t_node	*find_max(t_stack *b)
{
	t_node	*current;
	t_node	*max;

	if (!b || !b->top)
		return (NULL);
	current = b->top;
	max = b->top;
	while (current)
	{
		if (current->index > max->index)
			max = current;
		current = current->next;
	}
	return (max);
}

void	bring_to_top(t_stack *stack, t_node *target)
{
	int		pos;
	int		size;
	t_node	*current;

	if (!stack || !stack->top || !target)
		return ;
	pos = 0;
	size = stack->size;
	current = stack->top;
	while (current && current != target)
	{
		current = current->next;
		pos++;
	}
	if (!current)
		return ;
	if (pos <= size / 2)
		while (stack->top != target)
			rotate_stack_silent(stack);
	else
		while (stack->top != target)
			reverse_rotate_stack_silent(stack);
}

void	restore_to_a(t_stack *a, t_stack *b)
{
	t_node	*max;

	while (b->size > 0)
	{
		max = find_max(b);
		bring_to_top(b, max);
		pa(a, b);
	}
}

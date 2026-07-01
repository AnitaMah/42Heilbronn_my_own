/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 14:19:31 by jdhamoda          #+#    #+#             */
/*   Updated: 2026/06/01 14:49:42 by jdhamoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_rr(t_stack **stack)
{
	t_stack	*last;
	t_stack	*prev;

	if (!*stack || !(*stack)->next)
		return ;
	prev = *stack;
	while (prev->next->next)
		prev = prev->next;
	last = prev->next;
	prev->next = NULL;
	last->next = *stack;
	*stack = last;
}

void	rra(t_stack **stack1)
{
	ft_rr(stack1);
	write(1, "rra\n", 4);
}

void	rrb(t_stack **stack2)
{
	ft_rr(stack2);
	write(1, "rrb\n", 4);
}

void	rrr(t_stack **a, t_stack **b)
{
	ft_rr(a);
	ft_rr(b);
	write(1, "rrr\n", 4);
}

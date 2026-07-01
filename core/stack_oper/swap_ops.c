/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 14:16:56 by jdhamoda          #+#    #+#             */
/*   Updated: 2026/06/01 15:24:22 by jdhamoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_s(t_stack **stack)
{
	t_stack	*tmp;

	if (!(*stack) || !((*stack)->next))
		return ;
	tmp = *stack;
	*stack = (*stack)->next;
	tmp->next = (*stack)->next;
	(*stack)->next = tmp;
}

void	sa(t_stack **stack1)
{
	ft_s(stack1);
	write(1, "sa\n", 3);
}

void	sb(t_stack **stack2)
{
	ft_s(stack2);
	write(1, "sb\n", 3);
}

void	ss(t_stack **stack1, t_stack **stack2)
{
	ft_s(stack1);
	ft_s(stack2);
	write(1, "ss\n", 3);
}

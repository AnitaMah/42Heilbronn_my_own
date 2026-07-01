/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 14:17:25 by jdhamoda          #+#    #+#             */
/*   Updated: 2026/06/01 14:26:57 by jdhamoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_r(t_stack **stack)
{
	t_stack	*head;

	head = *stack;
	if (!(*stack) || !((*stack)->next))
		return ;
	*stack = head->next;
	head->next = NULL;
	last_node(*stack)->next = head;
}

void	ra(t_stack **stack1)
{
	ft_r(stack1);
	write(1, "ra\n", 3);
}

void	rb(t_stack **stack2)
{
	ft_r(stack2);
	write(1, "rb\n", 3);
}

void	rr(t_stack **stack1, t_stack **stack2)
{
	ft_r(stack1);
	ft_r(stack2);
	write(1, "rr\n", 3);
}

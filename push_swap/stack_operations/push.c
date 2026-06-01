/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 21:59:32 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/01 21:59:32 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pb(t_stack *a, t_stack *b)
{
	push_stack(a, b);
	write(1, "pb\n", 3);
}

void	pb(t_stack *a, t_stack *b)
{
	push_stack(a, b);
	write(1, "pb\n", 3);
}
void	pa(t_stack *a, t_stack *b)
{
	push_stack(b, a);
	write(1, "pa\n", 3);
}

static void	push_stack(t_stack *src, t_stack *dest)
{
	t_node	*node;

	if (!src || src->size == 0)
		return ;
	node = src->top;
	src->top = node->next;
	if (src->top)
		src->top->prev = NULL;
	else
		src->bottom = NULL;
	src->size--;
	node->next = dest->top;
	node->prev = NULL;
	if (dest->top)
		dest->top->prev = node;
	else
		dest->bottom = node;
	dest->top = node;
	dest->size++;
}

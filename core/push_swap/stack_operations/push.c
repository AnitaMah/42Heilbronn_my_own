/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:02:56 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/17 14:09:18 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

static void	push_stack(t_stack *src, t_stack *dest)
{
	t_node	*tmp;

	if (!src->top)
		return ;
	tmp = src->top;
	src->top = tmp->next;
	if (src->top)
		src->top->prev = NULL;
	else
		src->bottom = NULL;
	tmp->prev = NULL;
	tmp->next = dest->top;
	if (dest->top)
		dest->top->prev = tmp;
	else
		dest->bottom = tmp;
	dest->top = tmp;
	src->size--;
	dest->size++;
}

void	pb(t_stack *a, t_stack *b)
{
	push_stack(a, b);
	op_counter(OP_PB);
	write(1, "pb\n", 3);
}

void	pa(t_stack *a, t_stack *b)
{
	push_stack(b, a);
	op_counter(OP_PA);
	write(1, "pa\n", 3);
}

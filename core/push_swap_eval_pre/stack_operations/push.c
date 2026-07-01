/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:02:56 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/26 17:17:44 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * @brief Moves the top element from one stack to another.
 * @param src The source stack to pop from.
 * @param dest The destination stack to push to.
 */

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

/**
 * @brief Pushes the top element of stack A to stack B.
 * @param a The source stack A.
 * @param b The destination stack B.
 */

void	pb(t_stack *a, t_stack *b)
{
	push_stack(a, b);
	op_counter(OP_PB);
	if (!supress_output(-1))
		write(1, "pb\n", 3);
}

/**
 * @brief Pushes the top element of stack B to stack A.
 * @param a The destination stack A.
 * @param b The source stack B.
 */

void	pa(t_stack *a, t_stack *b)
{
	push_stack(b, a);
	op_counter(OP_PA);
	if (!supress_output(-1))
		write(1, "pa\n", 3);
}

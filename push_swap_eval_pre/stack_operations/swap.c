/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:18:54 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/26 17:19:27 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * @brief Swaps the values and indices of the top two elements of a stack.
 * @param stack The stack on which the swap operation is performed.
 */

static void	swap_stack(t_stack *stack)
{
	int	tmp_val;
	int	tmp_idx;

	if (!stack || stack->size < 2)
		return ;
	tmp_val = stack->top->value;
	stack->top->value = stack->top->next->value;
	stack->top->next->value = tmp_val;
	tmp_idx = stack->top->index;
	stack->top->index = stack->top->next->index;
	stack->top->next->index = tmp_idx;
}

/**
 * @brief Swaps the top two elements of stack A.
 * @param a The stack to perform the swap on.
 */

void	sa(t_stack *a)
{
	if (!a || a->size < 2)
		return ;
	swap_stack(a);
	op_counter(OP_SA);
	if (!supress_output(-1))
		write(1, "sa\n", 3);
}

/**
 * @brief Swaps the top two elements of stack B.
 * @param b The stack to perform the swap on.
 */

void	sb(t_stack *b)
{
	if (!b || b->size < 2)
		return ;
	swap_stack(b);
	op_counter(OP_SB);
	if (!supress_output(-1))
		write(1, "sb\n", 3);
}

/**
 * @brief Swaps the top two elements of both stack A and stack B.
 * @param a The first stack to perform the swap on.
 * @param b The second stack to perform the swap on.
 */

void	ss(t_stack *a, t_stack *b)
{
	if ((!a || a->size < 2) || (!b || b->size < 2))
		return ;
	swap_stack(a);
	swap_stack(b);
	op_counter(OP_SS);
	if (!supress_output(-1))
		write(1, "ss\n", 3);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_apply.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:08:04 by jdhamoda          #+#    #+#             */
/*   Updated: 2026/06/17 11:14:25 by jdhamoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

static void	auto_strategy(t_stack *a, t_stack *b, double disorder)
{
	if (a->size <= 5)
		sort_four_five(a, b, a->size);
	else if (a->size <= 100)
	{
		if (disorder < 0.2)
			selection_sort_adaptation(a, b);
		else
			chunk_sort(a, b);
	}
	else
	{
		if (disorder < 0.2)
			selection_sort_adaptation(a, b);
		else if (disorder < 0.5)
			chunk_sort(a, b);
		else
			radix_sort(a, b);
	}
}

static void	apply_strategy(t_stack *a, t_stack *b, t_flags *flags)
{
	if (a->size <= 5)
	{
		sort_four_five(a, b, a->size);
		return ;
	}
	if (flags->strategy == STRATEGY_SIMPLE)
		selection_sort_adaptation(a, b);
	else if (flags->strategy == STRATEGY_MEDIUM)
		chunk_sort(a, b);
	else
		radix_sort(a, b);
}

void	sort_stack(t_stack *a, t_stack *b, t_flags *flags, double disorder)
{
	if (a->size <= 1)
		return ;
	if (a->size == 2)
	{
		if (a->top->value > a->top->next->value)
			sa(a);
		return ;
	}
	if (flags->strategy != STRATEGY_ADAPTIVE)
		apply_strategy(a, b, flags);
	else
		auto_strategy(a, b, disorder);
	print_bench(flags, disorder);
}

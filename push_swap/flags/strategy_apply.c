/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_apply.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:08:04 by jdhamoda          #+#    #+#             */
/*   Updated: 2026/06/18 15:16:18 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

static void	auto_strategy(t_stack *a, t_stack *b, double disorder,
		t_flags *flags)
{
	if (a->size <= 5)
		sort_four_five(a, b, a->size, flags);
	else if (a->size <= 100)
	{
		if (disorder < 0.2)
			selection_sort_adaptation(a, b, flags);
		else
			chunk_sort(a, b, flags);
	}
	else
	{
		if (disorder < 0.2)
			selection_sort_adaptation(a, b, flags);
		else if (disorder < 0.5)
			chunk_sort(a, b, flags);
		else
			radix_sort(a, b, flags);
	}
}

static void	apply_strategy(t_stack *a, t_stack *b, t_flags *flags)
{
	if (a->size <= 5)
	{
		sort_four_five(a, b, a->size, flags);
		return ;
	}
	if (flags->strategy == STRATEGY_SIMPLE)
		selection_sort_adaptation(a, b, flags);
	else if (flags->strategy == STRATEGY_MEDIUM)
		chunk_sort(a, b, flags);
	else
		radix_sort(a, b, flags);
}

void	sort_stack(t_stack *a, t_stack *b, t_flags *flags, double disorder)
{
	if (a->size <= 1)
		return ;
	if (a->size == 2)
	{
		if (a->top->value > a->top->next->value)
			sa(a, flags);
	}
	if (flags->strategy != STRATEGY_ADAPTIVE)
		apply_strategy(a, b, flags);
	else
		auto_strategy(a, b, disorder, flags);
	if (flags->count_only)
	{
		print_count_only(flags);
		return ;
	}
	if (flags->bench)
		print_bench(flags, disorder);
}

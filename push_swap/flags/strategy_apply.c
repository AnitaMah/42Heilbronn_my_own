/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_apply.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:08:04 by jdhamoda          #+#    #+#             */
/*   Updated: 2026/06/25 17:27:29 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

static void	auto_strategy(t_stack *a, t_stack *b)
{
	if (a->size <= 100)
		chunk_sort(a, b);
	else
		radix_sort(a, b);
}

static void	sort_adaptive(t_stack *a, t_stack *b, double disorder)
{
	if (disorder < 0.25)
		selection_sort_adaptation(a, b);
	else if (disorder < 0.5)
		chunk_sort(a, b);
	else
		radix_sort(a, b);
}

static void	apply_strategy(t_stack *a, t_stack *b, t_flags *flags,
		double disorder)
{
	if (flags->strategy == STRATEGY_NONE)
		auto_strategy(a, b);
	else if (flags->strategy == STRATEGY_SIMPLE)
		selection_sort_adaptation(a, b);
	else if (flags->strategy == STRATEGY_MEDIUM)
		chunk_sort(a, b);
	else if (flags->strategy == STRATEGY_COMPLEX)
		radix_sort(a, b);
	else if (flags->strategy == STRATEGY_ADAPTIVE)
		sort_adaptive(a, b, disorder);
}

static int	handle_small_stack(t_stack *a, t_stack *b, t_flags *flags)
{
	if (a->size == 2 && flags->strategy == STRATEGY_NONE)
		return (sort_two(a), 1);
	if (a->size == 3 && flags->strategy == STRATEGY_NONE)
		return (sort_three(a), 1);
	if (a->size <= 5 && flags->strategy == STRATEGY_NONE)
		return (sort_four_five(a, b, a->size), 1);
	return (0);
}

void	sort_stack(t_stack *a, t_stack *b, t_flags *flags, double disorder)
{
	if (a->size <= 1)
		return ;
	if (handle_small_stack(a, b, flags))
	{
		print_bench(flags, disorder);
		return ;
	}
	apply_strategy(a, b, flags, disorder);
	print_bench(flags, disorder);
}

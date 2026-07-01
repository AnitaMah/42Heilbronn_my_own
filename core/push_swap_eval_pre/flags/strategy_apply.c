/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_apply.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:08:04 by jdhamoda          #+#    #+#             */
/*   Updated: 2026/06/26 13:00:03 by jdhamoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * @file strategy_selector.c
 * @brief Strategy routing and sorting core for push_swap.
 */

/**
 * @brief Selects a default sorting strategy based solely on stack size.
 * @param a Pointer to stack A.
 * @param b Pointer to stack B.
 */

static void	auto_strategy(t_stack *a, t_stack *b)
{
	if (a->size <= 100)
		chunk_sort(a, b);
	else
		radix_sort(a, b);
}

/**
 * @brief Selects a sorting strategy dynamically based on the disorder metric.
 * @param a Pointer to stack A.
 * @param b Pointer to stack B.
 * @param disorder Calculated structural data chaos metric.
 */
static void	sort_adaptive(t_stack *a, t_stack *b, double disorder)
{
	if (disorder < 0.25)
		selection_sort_adaptation(a, b);
	else if (disorder < 0.5)
		chunk_sort(a, b);
	else
		radix_sort(a, b);
}

/**
 * @brief Applies the designated sorting strategy
   corresponding to the program flags.
 * @param a Pointer to stack A.
 * @param b Pointer to stack B.
 * @param flags Pointer to the configuration structure
   containing the strategy mode.
 * @param disorder Calculated structural data chaos metric.
 */
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

/**
 * @brief Optimally sorts tiny stacks (sizes 2 through 5) 
   if no explicit strategy is specified.
 * @param a Pointer to stack A.
 * @param b Pointer to stack B.
 * @param flags Pointer to the configuration structure 
   containing the strategy mode.
 * @return 1 if a small stack sorting routine was 
   successfully executed, 0 otherwise.
 */
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

/**
 * @brief Main entry point for sorting the stacks and triggering benchmarks.
 * @param a Pointer to stack A.
 * @param b Pointer to stack B.
 * @param flags Pointer to the configuration structure containing 
   diagnostic options.
 * @param disorder Calculated structural data chaos metric.
 */
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

/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* strategy_apply.c                                   :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/16 17:08:04 by jdhamoda          #+#    #+#             */
/* Updated: 2026/06/18 16:34:01 by anmakhov         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/*
 * auto_strategy - Selects a sorting algorithm based on stack size and disorder.
 * @a: Pointer to stack A.
 * @b: Pointer to stack B.
 * @disorder: A coefficient representing how unsorted the stack is.
 * @flags: Pointer to the program configuration flags.
 */
static void auto_strategy(t_stack *a, t_stack *b, double disorder,
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

/*
 * sort_appadptive - Applies adaptive sorting based on the disorder level.
 * @a: Pointer to stack A.
 * @b: Pointer to stack B.
 * @flags: Pointer to the program configuration flags.
 * @disorder: A coefficient representing the level of disorder.
 */
static void sort_appadptive(t_stack *a, t_stack *b, t_flags *flags,
        double disorder)
{
    if (disorder < 0.25)
        selection_sort_adaptation(a, b, flags);
    else if (disorder >= 0.25 && disorder < 0.5)
        chunk_sort(a, b, flags);
    else if (disorder > 0.5)
        radix_sort(a, b, flags);
}

/*
 * apply_strategy - Decides the sorting strategy based on provided user flags
 * or initiates an adaptive selection process.
 * @a: Pointer to stack A.
 * @b: Pointer to stack B.
 * @disorder: A coefficient representing the level of disorder.
 * @flags: Pointer to the program configuration flags.
 */
static void apply_strategy(t_stack *a, t_stack *b, double disorder,
        t_flags *flags)
{
    if (flags->strategy == STRATEGY_SIMPLE)
        selection_sort_adaptation(a, b, flags);
    else if (flags->strategy == STRATEGY_MEDIUM)
        chunk_sort(a, b, flags);
    else if (flags->strategy == STRATEGY_COMPLEX)
        radix_sort(a, b, flags);
    else
    {
        if (a->size <= 5)
        {
            sort_four_five(a, b, a->size, flags);
            return ;
        }
        else
            sort_appadptive(a, b, flags, disorder);
    }
}

/*
 * sort_stack - Main entry point to sort the stack using the configured strategy.
 * Handles small stack optimizations, strategy application, and logging.
 * @a: Pointer to stack A.
 * @b: Pointer to stack B.
 * @flags: Pointer to the program configuration flags.
 * @disorder: A coefficient representing the level of disorder.
 */
void    sort_stack(t_stack *a, t_stack *b, t_flags *flags, double disorder)
{
    if (a->size <= 1)
        return ;
    if (a->size == 2)
    {
        if (a->top->value > a->top->next->value)
            sa(a, flags);
    }
    if (flags->strategy != STRATEGY_ADAPTIVE)
        apply_strategy(a, b, disorder, flags);
    else
        auto_strategy(a, b, disorder, flags);
    if (flags->bench)
        print_bench(flags, disorder);
}

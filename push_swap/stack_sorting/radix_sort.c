/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:07:04 by jdhamoda          #+#             */
/*   Updated: 2026/06/15 15:19:15 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

static void distribute_by_bit(t_stack *a, t_stack *b, int bit)
{
    int size;

    size = a->size;
    // Одиничний прохід: без зайвих вкладених циклів
    while (size--)
    {
        if (((a->top->index >> bit) & 1) == 0)
            pb(a, b);
        else
            ra(a);
    }
}

static void collect_from_b(t_stack *a, t_stack *b)
{
    // Одиничний прохід: просто повертаємо все з B в A
    while (b->size > 0)
        pa(a, b);
}

static void process_bits(t_stack *a, t_stack *b, int max_bits)
{
    int i;

    i = 0;
    while (i < max_bits)
    {
        // Переміщення елементів відповідно до біта
        distribute_by_bit(a, b, i);

        // Повернення елементів назад в стек А
        collect_from_b(a, b);
        i++;
    }
}

static int  get_max_bits(t_stack *a)
{
    int     max;
    int     bits;

    if (!a || a->size == 0)
        return (0);
    max = a->size - 1;

    bits = 0;
    while ((max >> bits) != 0)
        bits++;
    return (bits);
}

void    radix_sort(t_stack *a, t_stack *b)
{
    int max_bits;

    if (!a || a->size <= 1)
        return ;
    normalize_index(a);
    max_bits = get_max_bits(a);

    // Використовуємо функцію-обгортку для проходу по бітах
    process_bits(a, b, max_bits);
}

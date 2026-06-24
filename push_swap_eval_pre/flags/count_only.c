/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* count_only.c                                       :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/18 15:17:50 by anmakhov          #+#    #+#             */
/* Updated: 2026/06/18 15:17:51 by anmakhov         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/*
 * print_count_only - Prints the total number of operations performed
 * if the count_only flag is enabled in the configuration.
 * * @apply: Pointer to the flags structure containing program settings.
 */
void    print_count_only(t_flags *apply)
{
    int total;

    if (!apply->count_only)
        return ;
    total = op_counter(OP_TOTAL);
    ft_putnbr_fd(total, 1);
    ft_putchar_fd('\n', 1);
}
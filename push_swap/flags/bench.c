/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 10:57:06 by jdhamoda          #+#    #+#             */
/*   Updated: 2026/06/18 16:05:33 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

int	op_counter(int mode)
{
	static int	c[OP_TOTAL];
	static int	total;
	int			i;

	if (mode == -1)
	{
		i = 0;
		total = 0;
		while (i < OP_TOTAL)
			c[i++] = 0;
		return (0);
	}
	if (mode >= 0 && mode < OP_TOTAL)
	{
		c[mode]++;
		total++;
		return (c[mode]);
	}
	if (mode == OP_TOTAL)
		return (total);
	if (mode >= 12 && mode < 23)
		return (c[mode - 12]);
	return (0);
}

static void	write_disorder(double disorder)
{
	int	percent;
	int	decimals;

	percent = (int)(disorder * 100.0);
	decimals = (int)(disorder * 10000.0) % 100;
	ft_putstr_fd("[bench] disorder: ", 2);
	ft_putnbr_fd(percent, 2);
	ft_putchar_fd('.', 2);
	if (decimals < 10)
		ft_putchar_fd('0', 2);
	ft_putnbr_fd(decimals, 2);
	ft_putstr_fd("%\n", 2);
}

static void	write_strategy(int strat, double disorder)
{
	ft_putstr_fd("[bench] strategy: ", 2);
	if (strat == STRATEGY_SIMPLE)
		ft_putstr_fd("Simple / O(n^2)\n", 2);
	else if (strat == STRATEGY_MEDIUM)
		ft_putstr_fd("Medium / O(n*sqrt(n))\n", 2);
	else if (strat == STRATEGY_COMPLEX)
		ft_putstr_fd("Complex / O(n log n)\n", 2);
	else if (disorder < 0.2)
		ft_putstr_fd("Adaptive / O(n^2)\n", 2);
	else if (disorder < 0.5)
		ft_putstr_fd("Adaptive / O(n*sqrt(n))\n", 2);
	else
		ft_putstr_fd("Adaptive / O(n log n)\n", 2);
}

static void	write_op_counts(void)
{
	ft_putstr_fd("[bench] sa: ", 2);
	ft_putnbr_fd(op_counter(12), 2);
	ft_putstr_fd(" sb: ", 2);
	ft_putnbr_fd(op_counter(13), 2);
	ft_putstr_fd(" ss: ", 2);
	ft_putnbr_fd(op_counter(14), 2);
	ft_putstr_fd(" pa: ", 2);
	ft_putnbr_fd(op_counter(15), 2);
	ft_putstr_fd(" pb: ", 2);
	ft_putnbr_fd(op_counter(16), 2);
	ft_putstr_fd(" ra: ", 2);
	ft_putnbr_fd(op_counter(17), 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("[bench] rb: ", 2);
	ft_putnbr_fd(op_counter(18), 2);
	ft_putstr_fd(" rr: ", 2);
	ft_putnbr_fd(op_counter(19), 2);
	ft_putstr_fd(" rra: ", 2);
	ft_putnbr_fd(op_counter(20), 2);
	ft_putstr_fd(" rrb: ", 2);
	ft_putnbr_fd(op_counter(21), 2);
	ft_putstr_fd(" rrr: ", 2);
	ft_putnbr_fd(op_counter(22), 2);
	ft_putchar_fd('\n', 2);
}

void	print_bench(t_flags *flags, double disorder)
{
	if (!flags->bench)
		return ;
	write_disorder(disorder);
	write_strategy(flags->strategy, disorder);
	ft_putstr_fd("[bench] total_ops: ", 2);
	ft_putnbr_fd(op_counter(11), 2);
	ft_putchar_fd('\n', 2);
	write_op_counts();
}

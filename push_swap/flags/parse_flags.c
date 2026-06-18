/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 12:53:17 by jdhamoda          #+#    #+#             */
/*   Updated: 2026/06/18 15:00:24 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"
#include <stdlib.h>
#include <unistd.h>

int	is_flag(char *s, char *flag)
{
	return (s && flag && ft_strncmp(s, flag, ft_strlen(flag) + 1) == 0);
}

static void	error_exit(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

void	parse_flags(int argc, char **argv, t_flags *flags)
{
	int	i;

	flags->strategy = STRATEGY_ADAPTIVE;
	flags->bench = 0;
	flags->count_only = 0;
	i = 1;
	while (i < argc)
	{
		if (is_flag(argv[i], "--simple"))
			flags->strategy = STRATEGY_SIMPLE;
		else if (is_flag(argv[i], "--medium"))
			flags->strategy = STRATEGY_MEDIUM;
		else if (is_flag(argv[i], "--complex"))
			flags->strategy = STRATEGY_COMPLEX;
		else if (is_flag(argv[i], "--adaptive"))
			flags->strategy = STRATEGY_ADAPTIVE;
		else if (is_flag(argv[i], "--bench"))
			flags->bench = 1;
		else if (is_flag(argv[1], "--count_only"))
			flags->count_only = 1;
		else if (argv[i][0] == '-' && argv[i][1] == '-')
			error_exit();
		i++;
	}
}

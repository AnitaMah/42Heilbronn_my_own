/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 12:53:17 by jdhamoda          #+#    #+#             */
/*   Updated: 2026/06/26 13:25:10 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * @file flags_parser.c
 * @brief Flag parsing and validation utilities for push_swap configuration.
 */

/**
 * @brief Compares an argument string against a specific target flag.
 * @param s The input string from command line arguments.
 * @param flag The specific flag string to match against.
 * @return 1 if the strings match exactly, 0 otherwise.
 */
int	is_flag(char *s, char *flag)
{
	return (s && flag && ft_strncmp(s, flag, ft_strlen(flag) + 1) == 0);
}

/**
 * @brief Prints a standardized error message to
   stderr and terminates the program.
 */
static void	error_exit(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

/**
 * @brief Parses command line arguments to configure
   sorting strategies and benchmark modes.
 * @param argc Total number of command line arguments.
 * @param argv Array of command line argument strings.
 * @param flags Pointer to the configuration structure to populate.
 */
void	parse_flags(int argc, char **argv, t_flags *flags)
{
	int	i;

	flags->strategy = STRATEGY_NONE;
	flags->bench = 0;
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
		else if (argv[i][0] == '-' && argv[i][1] == '-')
			error_exit();
		i++;
	}
}

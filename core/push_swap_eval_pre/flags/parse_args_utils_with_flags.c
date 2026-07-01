/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils_with_flags.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:46:35 by jdhamoda          #+#    #+#             */
/*   Updated: 2026/06/26 12:55:08 by jdhamoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * @file argument_parser.c
 * @brief Argument parsing and split validation utilities for push_swap.
 */

/**
 * @brief Validates a split array string and frees it if invalid.
 * @param split The NULL-terminated array of strings to check.
 * @return 1 if valid and contains elements, 0 otherwise.
 */

static int	is_valid_split(char **split)
{
	if (!split || !split[0])
	{
		free_split(split);
		return (0);
	}
	return (1);
}

/**
 * @brief Checks if an argument is a configuration flag (starts with `--`).
 * @param s The string argument to evaluate.
 * @return 1 if the argument is a flag, 0 otherwise.
 */
static int	is_flag_arg(char *s)
{
	return (s && s[0] == '-' && s[1] == '-');
}

/**
 * @brief Splits a string by spaces and processes it based on the mode.
 * @param arg The space-separated string argument to process.
 * @param nums Array to store parsed integers (used in mode 1).
 * @param k Pointer to the current index tracking the position in the nums array.
 * @param mode `0` to count integers, `1` to parse and fill the array.
 * @return The count of words if mode is 0, or success status (1/0) if mode is 1.
 */
static int	process_split(char *arg, int *nums, int *k, int mode)
{
	char	**split;
	int		res;

	split = ft_split(arg, ' ');
	if (!is_valid_split(split))
		return (0);
	if (mode == 0)
		res = count_words_in_split(split);
	else
		res = fill_single_split(split, nums, k);
	free_split(split);
	return (res);
}

/**
 * @brief Iterates through arguments to count integers.
 * @param argc Total count of arguments.
 * @param argv Array of argument strings.
 * @param nums Target integer array to populate (used in mode 1).
 * @param mode `0` to calculate total integers, `1` to parse and store values.
 * @return Total number of arguments if mode is 0, `1` on success, 
 * or `0` on parsing failure.
 */
int	handle_args(int argc, char **argv, int *nums, int mode)
{
	int	i;
	int	k;
	int	total;

	i = 1;
	k = 0;
	total = 0;
	while (i < argc)
	{
		if (is_flag_arg(argv[i]))
		{
			i++;
			continue ;
		}
		if (mode == 0)
			total += process_split(argv[i], nums, &k, 0);
		else if (!process_split(argv[i], nums, &k, 1))
			return (0);
		i++;
	}
	if (mode == 0)
		return (total);
	return (1);
}

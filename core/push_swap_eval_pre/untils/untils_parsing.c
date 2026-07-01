/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   untils_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:22:11 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/26 12:38:47 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

/**
 * Frees a dynamically allocated 2D string array.
 * Iterates through each string pointer and frees it before the array.
 * @param arr The pointer to the array of strings to be freed.
 */

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
/**
 * Validates if a string represents a valid integer number.
 * Checks for signs and ensures only numeric characters exist.
 * @param s String to be validated.
 * @return 1 if valid, 0 if invalid.
 */

int	is_valid_number(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/**
 * Counts the number of elements in a NULL-terminated string array.
 * Iterates through the pointer array until the NULL terminator.
 * @param args The array of strings to count.
 * @return The integer count of strings.
 */

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

/**
 * Frees the argument array if it was dynamically split from a string.
 * Checks the argument count to determine if memory release is required.
 * @param argc The count of arguments provided to the program.
 * @param args The array of argument strings to potentially free.
 */

void	free_args_if_split(int argc, char **args)
{
	if (argc == 2)
		free_split(args);
}

/**
 * Fills an integer array with values parsed from a split string array.
 * Validates each string and stops if a parsing error is encountered.
 * @param split Array of strings containing numerical values.
 * @param nums Array to store the parsed integers.
 * @param k Pointer to the current index in the integer array.
 * @return 1 if success, 0 if parsing fails or invalid numbers.
 */

int	fill_single_split(char **split, int *nums, int *k)
{
	int	j;
	int	error;

	j = 0;
	while (split[j])
	{
		error = 0;
		if (!is_valid_number(split[j]))
			return (0);
		nums[*k] = ft_atoi_ps(split[j], &error);
		if (error)
			return (0);
		(*k)++;
		j++;
	}
	return (1);
}

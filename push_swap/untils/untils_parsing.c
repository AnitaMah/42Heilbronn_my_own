/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   untils_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:22:11 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/15 22:01:22 by jdhamoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

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

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	free_args_if_split(int argc, char **args)
{
	if (argc == 2)
		free_split(args);
}

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

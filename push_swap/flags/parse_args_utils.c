/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:46:35 by jdhamoda          #+#    #+#             */
/*   Updated: 2026/06/16 18:12:37 by jdhamoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

static int	is_valid_split(char **split)
{
	if (!split || !split[0])
	{
		free_split(split);
		return (0);
	}
	return (1);
}

static int	is_flag_arg(char *s)
{
	return (s && s[0] == '-' && s[1] == '-');
}

static int	process_split(char *arg, int *nums, int *k, int mode)
{
	char	**split;
	int		result;

	split = ft_split(arg, ' ');
	if (!is_valid_split(split))
		return (0);
	if (mode == 0)
		result = count_words_in_split(split);
	else
		result = fill_single_split(split, nums, k);
	free_split(split);
	return (result);
}

int	handle_args(int argc, char **argv, int *nums, int mode)
{
	int	i;
	int	total;
	int	k;

	i = 1;
	total = 0;
	k = 0;
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

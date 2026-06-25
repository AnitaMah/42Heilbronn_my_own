/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils_with_flags.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:46:35 by jdhamoda          #+#    #+#             */
/*   Updated: 2026/06/25 17:26:38 by anmakhov         ###   ########.fr       */
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

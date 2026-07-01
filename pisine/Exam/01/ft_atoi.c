/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 20:29:11 by username          #+#    #+#             */
/*   Updated: 2026/04/16 16:18:54 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	*move_iter_after_space(char *str, int *iter)
{
	while (str[*iter] == 32 || (str[*iter] >= 9 && str[*iter] <= 13))
	{
		(*iter)++;
	}
	return (iter);
}

int	calculate_a_sign(char *str, int *iter)
{
	int	sign = 1;

	while (str[*iter] == '-' || str[*iter] == '+')
	{
		if (str[*iter] == '-')
		{
			sign = -sign;
		}
		(*iter)++;
	}
	return (sign);
}

int	calculate_a_base(char *str, int *iter)
{
	int	result = 0;

	while (str[*iter] >= '0' && str[*iter] <= '9')
	{
		result = result * 10 + str[*iter] - '0';
		(*iter)++;
	}
	return (result);
}

int	ft_atoi(char *str)
{
	int	iter = 0;
	int	sign;
	int	result;

	move_iter_after_space(str, &iter);
	sign = calculate_a_sign(str, &iter);
	result = calculate_a_base(str, &iter);
	return (sign * result);
}
#include <stdio.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	k = ft_atoi(argv[1]);

	printf("%i", k);
	return (0);
}

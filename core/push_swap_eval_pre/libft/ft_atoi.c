/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 20:29:11 by username          #+#    #+#             */
/*   Updated: 2026/04/30 13:06:16 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*move_iter_after_space(const char *str, int *iter)
{
	while (str[*iter] == 32 || (str[*iter] >= 9 && str[*iter] <= 13))
	{
		(*iter)++;
	}
	return (iter);
}

int	calculate_a_sign(const char *str, int *iter)
{
	int	sign;

	sign = 1;
	if (str[*iter] == '-' || str[*iter] == '+')
	{
		if (str[*iter] == '-')
		{
			sign = -sign;
		}
		(*iter)++;
		if (str[*iter] == '+' || str[*iter] == '-')
		{
			return (0);
		}
	}
	return (sign);
}

int	calculate_a_base(const char *str, int *iter)
{
	int	result;

	result = 0;
	while (str[*iter] >= '0' && str[*iter] <= '9')
	{
		result = result * 10 + (str[*iter] - '0');
		(*iter)++;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	int	iter;
	int	sign;
	int	result;

	iter = 0;
	move_iter_after_space(str, &iter);
	sign = calculate_a_sign(str, &iter);
	result = calculate_a_base(str, &iter);
	return (sign * result);
}

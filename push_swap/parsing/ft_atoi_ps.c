/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_ps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhamoda <jdhamoda@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:45:20 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/15 21:46:42 by jdhamoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_file/push_swap.h"

static void	skip_spaces(const char *s, int *i)
{
	while (s[*i] == ' ' || (s[*i] >= 9 && s[*i] <= 13))
		(*i)++;
}

static int	handle_sign(const char *s, int *i)
{
	int	sign;

	sign = 1;
	if (s[*i] == '-' || s[*i] == '+')
	{
		if (s[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static long	parse_digits(const char *s, int *i, int *error, int sign)
{
	long	result;

	result = 0;
	if (s[*i] < '0' || s[*i] > '9')
		return (*error = 1, 0);
	while (s[*i] >= '0' && s[*i] <= '9')
	{
		result = result * 10 + (s[*i] - '0');
		if (sign == 1 && result > 2147483647)
			return (*error = 1, 0);
		if (sign == -1 && result > 2147483648)
			return (*error = 1, 0);
		(*i)++;
	}
	return (result);
}

int	ft_atoi_ps(const char *s, int *error)
{
	int		i;
	int		sign;
	long	value;

	i = 0;
	*error = 0;
	skip_spaces(s, &i);
	sign = handle_sign(s, &i);
	value = parse_digits(s, &i, error, sign);
	if (*error)
		return (0);
	if (s[i] != '\0')
		return (*error = 1, 0);
	return ((int)(value * sign));
}

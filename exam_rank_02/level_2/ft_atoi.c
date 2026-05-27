/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:32:21 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/20 18:50:59 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	*move_iter_after_spacewhite(char *str, int *iter)
{
	while (str[*iter] == 9 || (str[*iter] >= 9 && str[*iter] <= 13))
		(*iter)++;
	return (iter);
}

int	calculate_a_sign(char *str, int *iter)
{
	int	sign;

	sign = 1;
	if (str[*iter] == '+' || str[*iter] == '-')
	{
		if (str[*iter] == '-')
			sign = -1;
	}
	(*iter)++;
	return (sign);
}

int	calculate_a_base(char *str, int *iter)
{
	int	result;

	while (str[*iter] >= '0' && str[*iter] <= '9')
	{
		result = result * 10 + (str[*iter] - '0');
		(*iter)++;
	}
	return (result);
}

int	ft_atoi(char *str)
{
	int	iter;
	int	sign;
	int	res;

	iter = 0;
	move_iter_after_spacewhite(str, &iter);
	sign = calculate_a_sign(str, &iter);
	res = calculate_a_base(str, &iter);
	return (sign * res);
}

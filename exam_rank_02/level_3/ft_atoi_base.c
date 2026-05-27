/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 18:37:08 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/26 19:04:03 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	get_value(char c, int base)
{
	char	*digits = "0123456789abcdef";
	int		i = 0;

	while (i < base)
	{
		if (digits[i] == c || digits[i] - 32 == c)
			return (i);
		i++;
	}
	return (-1);
}

void move_iter_after_sp(const char *str, int *iter)
{
	while (str[*iter] == 32 || (str[*iter] >= 9 && str[*iter] <= 13))
		(*iter)++;
}
int calculate_a_sign(const char *str, int *iter)
{
	int sign = 1;
	if (str[*iter] == '-' || str[*iter] == '+')
	{
		if (str[*iter] == '-')
			sign = -1;
		(*iter)++;	
	}
	return (sign);
}

int calculate_a_base(const char *str, int str_base, int *iter)
{
	int res = 0;
	int vallue;

	vallue = get_value(str[*iter], str_base);
	while (vallue  != -1)
    {
        res = res * str_base + vallue;
        (*iter)++;
		vallue = get_value(str[*iter], str_base);
    }
	return (res);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int iter = 0;
	int sign;
	int res;
	if (str_base < 2 || str_base > 16)
		return (0);
	move_iter_after_sp(str, &iter);
	sign = calculate_a_sign(str, &iter);
	res = calculate_a_base(str, str_base, &iter);
	return (res * sign);
}
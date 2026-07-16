/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prime_sum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:02:28 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/09 16:03:50 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	is_prime(int nb)
{
	int	i;

	i = 2;
	if (nb < 2)
		return (0);
	while (i <= nb / i)
	{
		if (nb % i == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int i = 0;
	int res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

void	put_nbr(int nb)
{
	char	c;

	if (nb >= 10)
		put_nbr(nb / 10);
	c = (nb % 10) + '0';
	write(1, &c, 1);
}

void	add_prime_sum(int nb)
{
	int	sum;
	int	i;

	sum = 0;
	i = 2;
	while (i <= nb)
	{
		if (is_prime(i))
			sum += i;
		i++;
	}
	put_nbr(sum);
}

int	main(int argc, char **argv)
{
	int	nb;

	if (argc != 2)
	{
		write(1, "0\n", 2);
		return (0);
	}
	nb = ft_atoi(argv[1]);
	add_prime_sum(nb);
	write(1, "\n", 1);
	return (0);
}

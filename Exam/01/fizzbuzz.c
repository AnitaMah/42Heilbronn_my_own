/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fizzbuzz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:26:00 by username          #+#    #+#             */
/*   Updated: 2026/03/17 19:51:38 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnb(int nb)
{
	char	c;

	if (nb > 9)
	{
		ft_putnb((int) nb / 10);
	}
	ft_putchar(nb % 10 + '0');
}

void	checker(void)
{
	int	iter = 1;

	while (iter <= 100)
	{
		if (iter % 3 == 0 && iter % 5 != 0)
		{
			write(1, "fizz", 4);
		}
		if (iter % 5 == 0 && iter % 3 != 0)
		{
			write(1, "buzz", 4);
		}
		if (iter % 3 == 0 && iter % 5 == 0)
		{
			write(1, "fizzbuzz", 8);
		}
		if (!(iter % 3 == 0 || iter % 5 == 0))
		{
			ft_putnb(iter);
		}
		write(1, "\n", 1);
		iter++;
	}
}

int	main(void)
{
	checker();
	return (0);
}

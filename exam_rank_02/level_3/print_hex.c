/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 20:24:45 by anmakhov          #+#    #+#             */
/*   Updated: 2026/05/27 20:24:46 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	put_hex(unsigned int nb)
{
	const char	*base;

	base = "0123456789abcdef";
	if (nb >= 16)
		put_hex(nb / 16);
	write(1, &base[nb % 16], 1);
}

int	ft_atoi(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			break ;
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (nb);
}

int	main(int argc, char **argv)
{
	unsigned int	nb;

	if (argc == 2)
	{
		nb = (unsigned int)ft_atoi(argv[1]);
		put_hex(nb);
	}
	write(1, "\n", 1);
	return (0);
}
